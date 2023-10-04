/*  FixupMaterials
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

#include "material.hpp"
#include "project.h"
#include "spike/app_context.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/reflect/reflector.hpp"

std::string_view filters[]{
    ".sbt$",
    ".sbm$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .header = FixupMaterials_DESC " v" FixupMaterials_VERSION
                                  ", " FixupMaterials_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct ReflectedInstanceFriend : ReflectedInstance {
  using ReflectedInstance::rfStatic;
};

void AppProcessFile(AppContext *ctx) {
  BinReaderRef rd(ctx->GetStream());
  uint32 id;
  rd.Read(id);

  if (id != CompileFourCC("SBT") && id != CompileFourCC("SBM")) {
    throw es::InvalidHeaderError(id);
  }

  std::vector<MaterialVariant> materials;
  uint16 versions;
  rd.Read(versions);
  rd.ReadContainerLambda(materials, ReadMaterialVariant);

  for (auto &m : materials) {
    auto reflected = GetReflectedMaterial(m);
    ReflectorPureWrap refMaterial(reflected);

    const size_t numMembers = refMaterial.GetNumReflectedValues();
    for (size_t i = 0; i < numMembers; i++) {
      std::string_view memberName(
          static_cast<ReflectedInstanceFriend &>(reflected)
              .rfStatic->typeNames[i]);

      if (memberName.ends_with("Texture")) {
        std::string value(refMaterial.GetReflectedValue(i));
        std::transform(value.begin(), value.end(), value.begin(),
                       [](char c) -> char {
                         if (c == '/') {
                           return '\\';
                         }
                         return std::tolower(c);
                       });

        if (value.ends_with(".dds")) {
          value.replace(value.size() - 3, 3, "tga");
        }

        refMaterial.SetReflectedValue(i, value);
      }
    }
  }

  BinWritterRef wr(
      ctx->NewFile(std::string(ctx->workingFile.GetFullPath()) + ".fixed").str);
  wr.Write(id);
  wr.Write(versions);
  wr.WriteContainerLambda(materials,
                          [](BinWritterRef wr, const MaterialVariant &mtr) {
                            std::visit([&](auto &mtl) { wr.Write(mtl); }, mtr);
                          });
  std::string restBuffer = ctx->GetBuffer(-1, rd.Tell());
  wr.WriteContainer(restBuffer);
}
