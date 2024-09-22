/*  DumpScripts
    Copyright(C) 2024 Lukas Cone

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
#include "script/core.hpp"
#include "spike/app_context.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/reflect/reflector_xml.hpp"
#include "spike/util/pugiex.hpp"
#include <fstream>
#include <memory>

std::string_view filters[]{
    ".resources$", ".instances", ".level$",
    ".gameinfo$",  ".stats$",    ".session$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .multithreaded = false,
    .header = DumpScripts_DESC " v" DumpScripts_VERSION
                               ", " DumpScripts_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

void LoadScript(std::istream &str,
                std::vector<std::unique_ptr<Resource>> &resources);

std::map<std::string, std::vector<std::unique_ptr<Resource>>> classes_;

struct ResourceLink : ResourceRef {};

REFLECT(CLASS(ResourceLink), MEMBER(asAddress));

auto GetMakeChild(pugi::xml_node node, const std::string &name) {
  if (auto child = node.child(name.c_str()); child) {
    return child;
  } else {
    return node.append_child(name.c_str());
  }
}

void AppFinishContext() {
  for (auto &[_, cls] : classes_) {
    std::sort(cls.begin(), cls.end(), [](auto &res0, auto &res1) {
      return res0->__guid < res1->__guid;
    });
  }
  pugi::xml_document doc;
  for (auto &[name, cls] : classes_) {
    pugi::xml_node levelNode = GetMakeChild(doc, name);
    for (auto &c : cls) {
      ReflectorPureWrap wrap({c.get()->refl, c.get()});
      pugi::xml_node node = levelNode.append_child("item");
      node.append_attribute("class").set_value(c->refl->className);
      ReflectorXMLUtil::Save(wrap, node,
                             {ReflectorXMLUtil::Flags_StringAsAttribute});
    }
  }

  std::ofstream str("everything.xml");
  doc.save(str, "\t", pugi::format_indent_attributes);
}

void AppProcessFile(AppContext *ctx) {
  auto exploded = ctx->workingFile.Explode();
  std::string level(exploded.at(exploded.size() - 3));

  LoadScript(ctx->GetStream(), classes_[level]);
}
