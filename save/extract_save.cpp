/*  ExtractSaveResource
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
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "zlib.h"

std::string_view filters[]{
    ".SAV$",
};

static AppInfo_s appInfo{
    .header = ExtractSaveResource_DESC " v" ExtractSaveResource_VERSION
                                       ", " ExtractSaveResource_COPYRIGHT
                                       "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct Save {
  char name0[32];
  char name1[32];
  char profileName[16];
  uint32 unk0[3];
  float unk1;
  uint32 unk2[8];
};

struct SaveData {
  uint32 unk0[2];
  uint32 uncompressedSize;
  uint32 compressedSize;
  uint32 unk1; // crc??
};

void AppProcessFile(AppContext *ctx) {
  auto saveData =
      ctx->RequestFile(std::string(ctx->workingFile.GetFullPathNoExt()));
  BinReaderRef rd(*saveData.Get());
  SaveData hdr;
  rd.Read(hdr);

  std::string buffer;
  rd.ReadContainer(buffer, hdr.compressedSize);
  std::string outBuffer;
  outBuffer.resize(hdr.uncompressedSize);
  uLongf destSize = hdr.uncompressedSize;
  int state =
      uncompress(reinterpret_cast<Bytef *>(outBuffer.data()), &destSize,
                 reinterpret_cast<Bytef *>(buffer.data()), buffer.size());

  if (state != Z_OK) {
    throw std::runtime_error("Uncompress error");
  }

  BinWritterRef wr(
      ctx->NewFile(ctx->workingFile.ChangeExtension2("resources")).str);
  wr.WriteContainer(outBuffer);
}
