/*  ScanScripts
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
#include "script.hpp"
#include "spike/app_context.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/master_printer.hpp"
#include "spike/reflect/reflector.hpp"
#include <fstream>
#include <set>

std::string_view filters[]{
    ".resources$", ".instances", ".level$",
    ".gameinfo$",  ".stats$",    ".session$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .multithreaded = false,
    .header = ScanScripts_DESC " v" ScanScripts_VERSION
                               ", " ScanScripts_COPYRIGHT "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct ClassInfo {
  const reflectorStatic *ref;
  std::string name;
  std::set<std::string> members;
};

std::set<const reflectorStatic *> processedClasses;
std::map<std::string, ClassInfo> uniqueClasses;

void AppFinishContext_() {
  std::ofstream str("_classes_.cpp");
  for (auto &[n, c] : uniqueClasses) {
    if (!c.ref) {
      str << "REFLECT(CLASS(" << c.name << "),\n";
      for (auto &m : c.members) {
        str << "MEMBERNAME(" << m << ", \"" << m << "\"),\n";
      }
    }

    str.seekp(str.tellp() - 2);
    str << "\n);\n";
  }
}

void AppFinishContext() {
  std::ofstream str("_classes_.cpp");

  for (auto &[n, c] : uniqueClasses) {
    str << "REFLECT(CLASS(" << c.name << "),\n";
    if (c.ref) {
      for (auto &name : c.members) {
        size_t maxCommon = 0;
        size_t maxCommonIndex = 0;
        size_t minFirstMatch = 0;

        if (name == "__GUID" || name == "Package") {
          continue;
        }

        for (size_t m = 0; m < c.ref->nTypes; m++) {
          std::string_view mName(c.ref->typeNames[m]);
          const char *aliasName =
              c.ref->typeAliases ? c.ref->typeAliases[m] : "";
          std::string_view aName(aliasName ? aliasName : "");
          size_t lastIndex = 0;
          size_t numCommon = 0;
          int firstMatch = -1;

          for (auto c : mName) {
            auto cl = std::tolower(c);

            for (size_t i = lastIndex; i < name.size(); i++) {
              auto nl = std::tolower(name[i]);
              if (nl == cl) {
                if (firstMatch == -1) {
                  firstMatch = i;
                }
                numCommon++;
                lastIndex = i;
                break;
              }
            }
          }

          if (maxCommon < numCommon && minFirstMatch >= firstMatch) {
            maxCommon = numCommon;
            maxCommonIndex = m;
            minFirstMatch = firstMatch;
          }
        }

        if (maxCommon) {
          float ratio =
              (float)maxCommon /
              (float)std::max(name.size(),
                              strlen(c.ref->typeNames[maxCommonIndex]));

          if (ratio < 0.7f) {
            str << "//MEMBERNAME(" << c.ref->typeNames[maxCommonIndex] << ", \""
                << name << "\"),\n";
          } else {
            str << "MEMBERNAME(" << c.ref->typeNames[maxCommonIndex] << ", \""
                << name << "\"),\n";
          }
        } else if (c.ref->typeNames) {
          str << "//MEMBERNAME(" << c.ref->typeNames[maxCommonIndex] << ",\""
              << name << "\"),\n";
        }
      }
    } else {
      for (auto &m : c.members) {
        str << "MEMBER(" << m << ", \"" << m << "\"),\n";
      }
    }

    str.seekp(str.tellp() - 2);
    str << "\n);\n";
  }
}

void AppProcessFile(AppContext *ctx) {
  std::vector<ClassInfo> classes;

  auto NewClass = [&](std::string_view name) {
    if (!name.starts_with("class_")) {
      throw std::runtime_error("class must start with class_");
    }
    if (classes.size()) {
      std::string cname = classes.back().name;
      uniqueClasses.emplace(cname, std::move(classes.back()));
    }
    classes.clear();
    name.remove_prefix(6);
    std::string strName(name);
    auto found = reflectorStatic::Registry().find(std::string_view(strName));

    if (found != reflectorStatic::Registry().end()) {
      bool skipClass = processedClasses.contains(found->second);

      if (!skipClass) {
        processedClasses.emplace(found->second);
      }

      classes.emplace_back(ClassInfo{
          found->second,
          strName,
      });
    } else {
      classes.emplace_back(ClassInfo{
          nullptr,
          strName,
      });
      // PrintError("Cannot find reflected class: ", strName);
    }
  };

  auto NewMember = [&](std::string_view name, ValueType type) {
    if (classes.empty()) {
      return;
    }

    if (auto found = uniqueClasses.find(classes.back().name);
        found != uniqueClasses.end()) {
      found->second.members.emplace(name);
    } else {
      classes.back().members.emplace(name);
    }

    if (type == VL_SUBCLASS) {
      auto found = reflectorStatic::Registry().find(name);
      std::string strName(name);
      std::erase(strName, '_');

      if (found == reflectorStatic::Registry().end()) {
        strName = classes.back().name + strName;
        found = reflectorStatic::Registry().find(std::string_view(strName));
      }

      if (found != reflectorStatic::Registry().end()) {
        bool skipClass = processedClasses.contains(found->second);

        if (!skipClass) {
          processedClasses.emplace(found->second);
        }

        classes.emplace_back(ClassInfo{
            found->second,
            strName,
        });
      } else {
        classes.emplace_back(ClassInfo{nullptr, strName});
        // PrintError("Cannot find reflected class: ", strName);
      }

      return;
    }
  };

  ScriptParser parser{ctx->GetStream()};
  parser.newClass = NewClass;
  parser.newMember = NewMember;
  parser.newValue = [](auto) {};
  parser.subclassEnd = [&] {
    if (classes.empty()) {
      return;
    }

    std::string cname = classes.back().name;
    uniqueClasses.emplace(cname, std::move(classes.back()));
    classes.pop_back();
  };

  parser.Process();

  if (classes.empty()) {
    return;
  }

  std::string cname = classes.back().name;
  uniqueClasses.emplace(cname, std::move(classes.back()));
}
