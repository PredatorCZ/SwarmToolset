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
#include <string_view>
#include <iosfwd>

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

ScriptIterator GlobalResourcesIterator();
ScriptIterator GlobalInstancesIterator();
size_t FileSize(const CacheFile &file);
const CacheFile *GetFile(std::string_view str);
void GetFileData(const CacheFile &file, char *outBuffer, uint32_t position,
                 uint32_t dataToBeRead);
void AddCachePair(Cache *c, std::istream *s);
void PatchCache();
std::string MakeVirtualSlak();
} // namespace stcache
