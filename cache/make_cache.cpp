/*  StgameCache
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
#include "spike/app_context.hpp"
#include "spike/crypto/crc32.hpp"
#include "spike/crypto/jenkinshash3.hpp"
#include "spike/io/binreader.hpp"
#include "spike/io/binwritter.hpp"
#include "spike/io/stat.hpp"
#include "stcache_internal.hpp"
#include <map>
#include <mutex>
#include <set>
#include <zstd.h>

static AppInfo_s appInfo{
    .header = StgameCache_DESC " v" StgameCache_VERSION
                               ", " StgameCache_COPYRIGHT "Lukas Cone",
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct SubStream {
  size_t offset;
  uint32 size;
};

struct SubStreamCrc : SubStream {
  uint32 crc;
};

struct Stream {
  std::string streamPath;
  BinWritter_t<BinCoreOpenMode::NoBuffer> streamStore;
  size_t blobalOffset = 0;

  Stream(std::string &&path)
      : streamPath(std::move(path)), streamStore(streamPath) {}

  SubStreamCrc SendStream(std::istream &str, bool addNewline = false) {
    const size_t inputSize = BinReaderRef(str).GetSize();
    char buffer[0x10000];
    const size_t numChunks = inputSize / sizeof(buffer);
    const size_t restBytes = inputSize % sizeof(buffer);
    SubStreamCrc retVal;
    retVal.offset = streamStore.Tell();
    uint32 crc = 0;

    for (size_t i = 0; i < numChunks; i++) {
      str.read(buffer, sizeof(buffer));
      streamStore.WriteBuffer(buffer, sizeof(buffer));
      // crc = crc32b(crc, buffer, sizeof(buffer));
    }

    if (restBytes) {
      str.read(buffer, restBytes);
      streamStore.WriteBuffer(buffer, restBytes);
      // crc = crc32b(crc, buffer, restBytes);
    }

    if (addNewline) {
      streamStore.Write('\n');
    }

    retVal.size = streamStore.Tell() - retVal.offset;
    retVal.crc = crc;

    return retVal;
  }
};

using namespace stcache;

struct IFile {
  uint32 nameHash;
  CacheFileType type;
  SubStream location;

  bool operator<(const IFile &o) const {
    if (nameHash == o.nameHash) {
      return uint32(type) < uint32(o.type);
    }

    return nameHash < o.nameHash;
  }
};

using FileGroup = std::map<uint32, Stream>;

struct MakeContext : AppPackContext {
  std::string baseFile;
  std::map<CacheFileType, Stream> streams;
  std::mutex mtx;
  std::vector<IFile> files;
  std::map<CacheFileType, FileGroup> mergeableFiles;
  std::set<std::string> virtualLevels;
  std::set<std::string> fileNames;
  std::set<std::string> globalResources;
  std::set<std::string> globalInstances;
  //<crc, fileIndex>
  std::map<uint32, uint32> fileCrcs;

  MakeContext(std::string baseFile_, const AppPackStats &)
      : baseFile(std::move(baseFile_)) {}

  void SendFile(std::string_view path_, std::istream &stream) override {
    std::string strPath(path_);
    std::transform(strPath.begin(), strPath.end(), strPath.begin(),
                   [](char c) { return std::tolower(c); });
    std::string_view path(strPath);

    auto dot = path.find_last_of('.');

    if (dot == path.npos) {
      throw std::runtime_error("File not supported.");
    }

    auto ext = path.substr(dot + 1);
    CacheFileType fileType = FromExtension(ext);

    if (IsBundled(fileType)) {
      auto filePath = path.substr(0, dot);
      filePath = filePath.substr(0, filePath.find_last_of('/'));
      std::lock_guard lg(mtx);

      if (filePath.ends_with("globals/scripts")) {
        (fileType == CacheFileType::Resources ? globalResources
                                              : globalInstances)
            .emplace(path.substr(0, dot).substr(path.find_last_of('/') + 1));
      } else {
        auto &group = mergeableFiles[fileType];
        uint32 key = JenkinsHash3_(filePath);

        if (!group.contains(key)) {
          group.emplace(key, baseFile + std::string(ext) +
                                 std::to_string(JenkinsHash3_(filePath)));
        }

        group.at(key).SendStream(stream, true);
        return;
      }
    }

    std::string_view filePath(IncludeExtension(fileType) ? path
                                                         : path.substr(0, dot));

    std::lock_guard lg(mtx);

    if (!streams.contains(fileType)) {
      streams.emplace(fileType, baseFile + std::string(ext));
    }

    auto &curStream = streams.at(fileType);

    SubStreamCrc streamRange = curStream.SendStream(stream);

    /*if (auto found = fileCrcs.find(streamRange.crc); found != fileCrcs.end())
    { IFile curFile = files.at(found->second); curFile.nameHash =
    JenkinsHash3_(filePath); files.emplace_back(curFile);
      curStream.streamStore.Seek(streamRange.offset);
    } else {*/
    IFile curFile{
        .nameHash = JenkinsHash3_(filePath),
        .type = fileType,
        .location = streamRange,
    };

    fileCrcs.emplace(streamRange.crc, uint32(files.size()));
    files.emplace_back(curFile);
    // }

    fileNames.emplace(filePath);

    if (fileType == CacheFileType::Level) {
      const size_t folderInex = path.find_last_of('/');
      std::string_view filePart(path);
      filePart.remove_prefix(folderInex + 1);
      filePart.remove_suffix(6);

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

      auto found = levelNames.find(filePart);

      if (!es::IsEnd(levelNames, found)) {
        virtualLevels.emplace(found->second);
      } else {
        virtualLevels.emplace(filePart);
      }
    }
  }

  void Finish() override {

    {
      BinWritter outRefs(baseFile + ".refs");
      //outRefs.WriteContainer("Number of duplicates: " +
      //                       std::to_string(files.size() - fileCrcs.size()));
      //outRefs.Write('\n');

      for (auto &f : fileNames) {
        outRefs.WriteContainer(std::to_string(JenkinsHash3_(f)));
        outRefs.Write('\t');
        outRefs.WriteContainer(f);
        outRefs.Write('\n');
      }
    }

    for (auto &[type, mergedData] : mergeableFiles) {
      for (auto &[nameHash, stream] : mergedData) {
        files.emplace_back(IFile{
            .nameHash = nameHash,
            .type = type,
            .location =
                {
                    .offset = 0,
                    .size = uint32(stream.streamStore.Tell()),
                },
        });
      }
    }

    BinWritter outIdx(baseFile + ".stmod");
    BinWritter_t<BinCoreOpenMode::NoBuffer> outData(baseFile + ".dat");
    std::sort(files.begin(), files.end());

    Cache outCache;
    outCache.files.numItems = files.size();
    outCache.numVirtualLevels = virtualLevels.size();
    outCache.numGlobalInstances = globalInstances.size();
    outCache.numGlobalResources = globalResources.size();
    outIdx.Write(outCache);

    if (outCache.numVirtualLevels) {
      outCache.virtualLevels.pointer =
          outIdx.Tell() - offsetof(Cache, virtualLevels.pointer);

      for (auto &lvl : virtualLevels) {
        outIdx.WriteContainer(lvl);
        outIdx.Write('\0');
        outCache.virtualLevels.numItems += lvl.size() + 1;
      }
    }

    if (outCache.numGlobalResources) {
      outCache.globalResources.pointer =
          outIdx.Tell() - offsetof(Cache, globalResources.pointer);

      for (auto &lvl : globalResources) {
        outIdx.WriteContainer(lvl);
        outIdx.Write('\0');
        outCache.globalResources.numItems += lvl.size() + 1;
      }
    }

    if (outCache.numGlobalInstances) {
      outCache.globalInstances.pointer =
          outIdx.Tell() - offsetof(Cache, globalInstances.pointer);

      for (auto &lvl : globalInstances) {
        outIdx.WriteContainer(lvl);
        outIdx.Write('\0');
        outCache.globalInstances.numItems += lvl.size() + 1;
      }
    }

    outIdx.ApplyPadding(alignof(CacheBlock));
    outCache.blocks.pointer = outIdx.Tell() - offsetof(Cache, blocks.pointer);

    constexpr size_t BLOCK_SIZE = 0x40000;
    char block[BLOCK_SIZE]{};
    size_t blockAvail = BLOCK_SIZE;

    ZSTD_CCtx *zctx = ZSTD_createCCtx();
    std::string zBuffer;
    zBuffer.resize(ZSTD_compressBound(BLOCK_SIZE));

    auto WriteCompressedBlock = [&] {
      outCache.blocks.numItems++;
      const size_t dataSize = BLOCK_SIZE - blockAvail;

      const uint32 cSize = ZSTD_compressCCtx(
          zctx, zBuffer.data(), zBuffer.size(), block, dataSize, ZSTD_btultra);

      CacheBlock nBlock{
          .offset = outData.Tell(),
          .size = cSize,
          .crc = crc32b(0, zBuffer.data(), cSize),
      };

      outIdx.Write(nBlock);
      outData.WriteBuffer(zBuffer.data(), cSize);
      blockAvail = BLOCK_SIZE;
    };

    auto WriteUncompressedBlock = [&] {
      outCache.blocks.numItems++;
      const uint32 dataSize = BLOCK_SIZE - blockAvail;

      CacheBlock nBlock{
          .offset = outData.Tell(),
          .size = dataSize,
          .crc = crc32b(0, block, dataSize),
      };

      outIdx.Write(nBlock);
      outData.WriteBuffer(block, dataSize);
      blockAvail = BLOCK_SIZE;
    };

    auto WriteBlock = [&] {
      if (outCache.streamingBlocksBegin != -1) {
        WriteUncompressedBlock();
      } else {
        WriteCompressedBlock();
      }
    };

    size_t currentOffset = 0;

    auto StreamBlocks = [&](auto &stream) {
      es::Dispose(stream.streamStore);
      stream.blobalOffset = currentOffset;
      BinReader rd(stream.streamPath);
      size_t streamSize = rd.GetSize();
      currentOffset += streamSize;

      while (streamSize) {
        size_t blockFill = std::min(blockAvail, streamSize);
        streamSize -= blockFill;
        rd.ReadBuffer(block + (BLOCK_SIZE - blockAvail), blockFill);
        blockAvail -= blockFill;

        if (blockAvail == 0) {
          WriteBlock();
        }
      }

      es::Dispose(rd);
      es::RemoveFile(stream.streamPath);
    };

    for (auto &[type, mergedData] : mergeableFiles) {
      for (auto &[name, stream] : mergedData) {
        StreamBlocks(stream);
      }
    }

    for (auto &[fileType, stream] : streams) {
      if (outCache.uncachedBlocksBegin == 0 &&
          fileType >= CacheFileType::UnknownUncachedBinaryResource) {
        outCache.uncachedBlocksBegin = outCache.blocks.numItems;
      } else if (outCache.streamingBlocksBegin == 0 &&
                 fileType >= CacheFileType::Ogg) {
        if (blockAvail > 0) {
          currentOffset += blockAvail;
          WriteBlock();
        }
        outCache.streamingBlocksBegin = outCache.blocks.numItems;
      }

      StreamBlocks(stream);
    }

    if (blockAvail != BLOCK_SIZE) {
      WriteBlock();
    }

    outIdx.ApplyPadding(alignof(CacheFile));

    outCache.files.pointer = outIdx.Tell() - offsetof(Cache, files.pointer);

    for (auto &f : files) {
      const size_t globOffset = [&] {
        if (auto found0 = mergeableFiles.find(f.type);
            found0 != mergeableFiles.end()) {
          if (auto found1 = found0->second.find(f.nameHash);
              found1 != found0->second.end()) {
            return found1->second.blobalOffset;
          }
        }

        return streams.at(f.type).blobalOffset;
      }();

      const uint32 microOffset = (globOffset + f.location.offset) % BLOCK_SIZE;
      uint32 tailSize = f.location.size;
      const uint32 numBlocks = [&]() -> uint32 {
        if (f.location.size <= BLOCK_SIZE - microOffset) {
          return 0;
        }

        const uint32 restSize = f.location.size - (BLOCK_SIZE - microOffset);
        tailSize = restSize % BLOCK_SIZE;

        return (restSize / BLOCK_SIZE) + 1;
      }();

      CacheFile file{
          .nameHash = f.nameHash,
          .fileType = f.type,
          .streamId = 0,
          .microOffset = microOffset,
          .numBlocks = numBlocks,
          .tailSize = tailSize,
          .blockOffset = uint32((globOffset + f.location.offset) / BLOCK_SIZE),
      };
      outIdx.Write(file);
    }

    outIdx.Seek(0);
    outIdx.Write(outCache);
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
