/*  SLAKCreate
    Copyright(C) 2023 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include "project.h"
#include "slakfile.hpp"
#include "spike/app_context.hpp"
#include "spike/io/binreader.hpp"
#include "spike/io/binwritter.hpp"
#include "spike/io/stat.hpp"
#include "spike/master_printer.hpp"
#include "zlib.h"
#include <map>
#include <mutex>
#include <set>
#include <thread>

static AppInfo_s appInfo{
    .header = SLAKCreate_DESC " v" SLAKCreate_VERSION ", " SLAKCreate_COPYRIGHT
                              "Lukas Cone",
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct SLAKFileEntryEx : SLAKFileEntry {
  std::string path;
};

struct Stream {
  std::string streamPath;
  BinWritter_t<BinCoreOpenMode::NoBuffer> streamStore;
  std::vector<SLAKFileEntryEx> files;

  Stream(std::string &&path)
      : streamPath(std::move(path)), streamStore(streamPath) {}
};

struct MakeContext : AppPackContext {
  std::string baseFile;
  std::map<uint32, Stream> streams;
  std::mutex mtx;

  MakeContext(std::string baseFile_, const AppPackStats &)
      : baseFile(std::move(baseFile_)) {}

  void SendFile(std::string_view path, std::istream &str) override {
    auto threadIdNative = std::this_thread::get_id();
    uint32 threadId = reinterpret_cast<const uint32 &>(threadIdNative);
    if (!streams.contains(threadId)) {
      std::lock_guard lg(mtx);
      streams.emplace(threadId, baseFile + std::to_string(threadId));
    }

    auto &stream = streams.at(threadId);
    BinReaderRef rd(str);
    std::string buffer;
    rd.ReadContainer(buffer, rd.GetSize());

    SLAKFileEntryEx curFile{};
    curFile.path = path;
    curFile.uncompressedSize = buffer.size();
    curFile.fileSize = curFile.uncompressedSize;
    curFile.creationTime =
        std::chrono::system_clock::now().time_since_epoch().count();
    curFile.offset = stream.streamStore.Tell();
    curFile.storeMethod = SLAKStoreMethod::Uncompressed;

    std::transform(curFile.path.begin(), curFile.path.end(),
                   curFile.path.begin(), [](char c) -> char {
                     if (c == '/') {
                       return '\\';
                     }

                     return std::tolower(c);
                   });

    if (curFile.uncompressedSize >
        appInfo.internalSettings->compressSettings.minFileSize) {
      std::string outBuffer;
      uLongf compressedSize = curFile.uncompressedSize + 32;
      outBuffer.resize(compressedSize);

      int state = compress2(reinterpret_cast<Bytef *>(outBuffer.data()),
                            &compressedSize,
                            reinterpret_cast<const Bytef *>(buffer.data()),
                            buffer.size(), Z_BEST_COMPRESSION);

      if (state != Z_OK) {
        throw std::runtime_error("Compression Error!");
      }

      uint32 ratio =
          ((float)compressedSize / (float)curFile.uncompressedSize) * 100;

      if (ratio <= appInfo.internalSettings->compressSettings.ratioThreshold) {
        curFile.fileSize = compressedSize;
        curFile.storeMethod = SLAKStoreMethod::ZLIB;
        stream.streamStore.WriteBuffer(outBuffer.data(), compressedSize);
      } else {
        if (appInfo.internalSettings->verbosity) {
          PrintInfo("Ratio fail ", ratio, "%% for ", path);
        }
        stream.streamStore.WriteContainer(buffer);
      }
    } else {
      stream.streamStore.WriteContainer(buffer);
    }

    stream.files.emplace_back(std::move(curFile));
  }

  void Finish() override {
    BinWritter wr(baseFile + ".slak");
    SLAKHeader hdr{};
    wr.Write(hdr);

    std::map<std::string, SLAKFileEntry> files;

    for (auto &[id, stream] : streams) {
      for (auto &f : stream.files) {
        files.emplace(f.path, f);
      }
    }

    hdr.numfiles = files.size();
    wr.Push();
    wr.Skip(sizeof(SLAKFileEntry) * files.size());
    wr.SetRelativeOrigin(wr.Tell(), false);

    for (auto &[name, entry] : files) {
      entry.nameOffset = wr.Tell();
      if (name.ends_with(".level")) [[unlikely]] {
        static const std::map<std::string_view, std::string_view> levelNames{
            {"level_bait", "Level_Bait"},
            {"level_brainbug", "Level_BrainBug"},
            {"level_bughives", "Level_BugHives"},
            {"level_commandship", "Level_CommandShip"},
            {"level_compound", "Level_Compound"},
            {"level_lostmarauder", "Level_LostMarauder"},
            {"level_offensive", "Level_Offensive"},
            {"level_outpost29", "Level_Outpost29"},
            {"level_plasmamountain", "Level_PlasmaMountain"},
            {"level_psi-ops", "Level_Psi-Ops"},
            {"level_stronghold", "Level_Stronghold"},
            {"level_twobridges", "Level_TwoBridges"},
            {"level_userinterface", "Level_UserInterface"},
            {"coop_bait", "COOP_Bait"},
            {"coop_compound", "COOP_Compound"},
            {"coop_outpost29", "COOP_Outpost29"},
            {"coop_plasmamountain", "COOP_PlasmaMountain"},
            {"coop_psiops", "COOP_PsiOps"},
            {"coop_stronghold", "COOP_Stronghold"},
            {"dm_bait", "DM_Bait"},
            {"dm_brimstone", "DM_Brimstone"},
            {"dm_compound", "DM_Compound"},
            {"dm_duel", "DM_Duel"},
            {"dm_hill", "DM_Hill"},
            {"dm_incinerator", "DM_Incinerator"},
            {"dm_offensive", "DM_Offensive"},
            {"dm_outpost29", "DM_Outpost29"},
        };

        const size_t folderInex = name.find_last_of('\\');
        std::string namec(name);

        if (folderInex != std::string::npos) {
          std::string_view filePart(namec);
          filePart.remove_prefix(folderInex + 1);
          filePart.remove_suffix(6);

          auto found = levelNames.find(filePart);

          if (!es::IsEnd(levelNames, found)) {
            namec.replace(namec.size() - (filePart.size() + 6),
                          found->second.size(), found->second.data());
          }
        }
        wr.WriteT(namec);

      } else {
        wr.WriteT(name);
      }
      hdr.maxFileSize = std::max(hdr.maxFileSize, entry.uncompressedSize);
    }

    hdr.filenamesSize = wr.Tell();
    wr.ResetRelativeOrigin(false);

    for (auto &[id, stream] : streams) {
      size_t globalOffset = wr.Tell();
      es::Dispose(stream.streamStore);
      BinReader_t<BinCoreOpenMode::NoBuffer> rd(stream.streamPath);
      const size_t fSize = rd.GetSize();
      char buffer[0x40000];
      const size_t numBlocks = fSize / sizeof(buffer);
      const size_t restBytes = fSize % sizeof(buffer);

      for (size_t b = 0; b < numBlocks; b++) {
        rd.Read(buffer);
        wr.Write(buffer);
      }

      if (restBytes) {
        rd.ReadBuffer(buffer, restBytes);
        wr.WriteBuffer(buffer, restBytes);
      }

      es::RemoveFile(stream.streamPath);

      for (auto &f : stream.files) {
        files.at(f.path).offset += globalOffset;
      }
    }

    wr.Pop();

    for (auto &[name, entry] : files) {
      wr.Write(entry);
    }

    wr.Seek(0);
    wr.Write(hdr);
  }
};

AppPackContext *AppNewArchive(const std::string &folder,
                              const AppPackStats &stats) {
  auto file = folder;
  while (file.back() == '/') {
    file.pop_back();
  }

  return new MakeContext(std::move(file), stats);
}
