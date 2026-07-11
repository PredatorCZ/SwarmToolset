/*  LibSwarm
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

#pragma once
#include "settings.hpp"
#include <cstdint>
#include <iosfwd>
#include <string>
#include <string_view>

namespace stcache {
struct Cache;
struct CacheFile;

struct ScriptIterator {
  uint16_t remSize;
  std::string_view current;

  std::string_view Next() {
    if (remSize == 0) {
      return {};
    }

    const size_t found = current.find_first_of('\0');
    std::string_view retVal(current.substr(0, found));
    current.remove_prefix(found + 1);
    remSize--;
    return retVal;
  }
};

ScriptIterator SW_EXTERN GlobalResourcesIterator();
ScriptIterator SW_EXTERN GlobalInstancesIterator();
size_t SW_EXTERN FileSize(const CacheFile &file);
const CacheFile SW_EXTERN *GetFile(std::string_view str);
void SW_EXTERN GetFileData(const CacheFile &file, char *outBuffer,
                           uint32_t position, uint32_t dataToBeRead);
void SW_EXTERN AddCachePair(Cache *c, std::istream *s);
void SW_EXTERN PatchCache();
std::string SW_EXTERN MakeVirtualSlak();
} // namespace stcache
