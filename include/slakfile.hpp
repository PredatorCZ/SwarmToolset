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

enum class SLAKStoreMethod : uint32_t { None, ZLIB, Uncompressed };

struct SLAKFileEntry {
  uint32_t nameOffset;
  uint64_t creationTime;
  uint32_t fileSize;
  uint32_t uncompressedSize;
  uint64_t offset;
  SLAKStoreMethod storeMethod{};
  uint32_t pad;
};

static constexpr std::string_view SLAKHEADER{"SlackPackFile  "};
struct SLAKHeader {
  char id[16] = "SlackPackFile  ";
  uint32_t filesOffset = sizeof(SLAKHeader);
  uint32_t filesSize = sizeof(SLAKFileEntry);
  uint32_t constants[2]{4608, 4};
  uint32_t numfiles;
  uint32_t filenamesSize;
  uint32_t maxFileSize = 0;
};
