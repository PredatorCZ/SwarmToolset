/*  DumpSignature
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

#include "nlohmann/json.hpp"
#include "project.h"
#include "spike/app_context.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/io/fileinfo.hpp"

std::string_view filters[]{
    "_signature.sbt$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .header = DumpSignature_DESC " v" DumpSignature_VERSION
                                 ", " DumpSignature_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

void AppProcessFile(AppContext *ctx) {
  BinReaderRef rd(ctx->GetStream());
  std::string id;
  rd.ReadString(id);

  if (id != "SBT_SIGN") {
    throw es::InvalidHeaderError(std::string_view(id));
  }

  uint16 versions;
  rd.Read(versions);
  std::vector<std::string> usedFiles;

  rd.ReadContainerLambda(
      usedFiles, [](BinReaderRef rd, std::string &str) { rd.ReadString(str); });

  nlohmann::json main(usedFiles);

  ctx->NewFile(ctx->workingFile.ChangeExtension2("json")).str << std::setw(2)
                                                              << main;
}
