/*  SLAKExtract
    Copyright(C) 2017-2022 Lukas Cone

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
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "zlib.h"

std::string_view filters[]{
    ".slak$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .header = SLAKExtract_DESC " v" SLAKExtract_VERSION
                               ", " SLAKExtract_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

void AppProcessFile(AppContext *ctx) {
  SLAKHeader hdr;
  BinReaderRef rd(ctx->GetStream());
  rd.Read(hdr);

  if (hdr.id != SLAKHEADER) {
    throw es::InvalidHeaderError(std::string_view(hdr.id));
  }

  rd.Seek(hdr.filesOffset);
  std::vector<SLAKFileEntry> files;
  rd.ReadContainer(files, hdr.numfiles);
  std::string names;
  rd.ReadContainer(names, hdr.filenamesSize);
  auto ectx = ctx->ExtractContext();

  if (ectx->RequiresFolders()) {
    for (auto &f : files) {
      AFileInfo path(names.data() + f.nameOffset);
      std::string strPath(path.GetFolder());
      std::transform(strPath.begin(), strPath.end(), strPath.begin(),
                     [](char c) { return std::tolower(c); });
      ectx->AddFolderPath(strPath);
    }

    ectx->GenerateFolders();
  }

  std::string dataBuffer;
  std::string outDataBuffer;

  for (auto &f : files) {
    AFileInfo path(names.data() + f.nameOffset);
    std::string strPath(path.GetFullPath());
    std::transform(strPath.begin(), strPath.end(), strPath.begin(),
                   [](char c) { return std::tolower(c); });
    ectx->NewFile(strPath);
    rd.Seek(f.offset);
    rd.ReadContainer(dataBuffer, f.fileSize);

    if (f.storeMethod == SLAKStoreMethod::ZLIB) {
      outDataBuffer.resize(f.uncompressedSize);
      z_stream infstream;
      infstream.zalloc = Z_NULL;
      infstream.zfree = Z_NULL;
      infstream.opaque = Z_NULL;
      infstream.avail_in = f.fileSize;
      infstream.next_in = reinterpret_cast<Bytef *>(&dataBuffer[0]);
      infstream.avail_out = outDataBuffer.size();
      infstream.next_out = reinterpret_cast<Bytef *>(&outDataBuffer[0]);
      inflateInit(&infstream);
      int state = inflate(&infstream, Z_FINISH);
      inflateEnd(&infstream);

      if (state < 0) {
        throw std::runtime_error(infstream.msg);
      }

      ectx->SendData(outDataBuffer);
    } else {
      ectx->SendData(dataBuffer);
    }
  }
}

size_t AppExtractStat(request_chunk requester) {
  auto buffer = requester(0, sizeof(SLAKHeader));
  auto hdr = reinterpret_cast<const SLAKHeader *>(buffer.data());
  return hdr->numfiles;
}
