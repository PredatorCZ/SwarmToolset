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
#include "pugixml.hpp"
#include "spike/app_context.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/reflect/reflector_xml.hpp"
#include <set>

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
  pugi::xml_document doc;
  std::set<std::string> allTextures;

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
                         if (c == '\\') {
                           return '/';
                         }
                         return std::tolower(c);
                       });

        allTextures.emplace(value);
      }
    }

    ReflectorXMLUtil::SaveV2a(refMaterial, doc.append_child(refMaterial.GetClassName().data()),
                              ReflectorXMLUtil::Flags_StringAsAttribute);
  }

  std::string buffer("\n");

  for(auto &t : allTextures) {
    buffer.append("    ");
    buffer.append(t);
    buffer.push_back('\n');
  }

  doc.prepend_child("textures").append_buffer(buffer.data(),buffer.size());

  doc.save(
      ctx->NewFile(std::string(ctx->workingFile.GetFullPath()) + ".xml").str,
      "    ", pugi::format_default | pugi::format_indent_attributes);
}
