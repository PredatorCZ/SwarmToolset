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
#include "stcache.hpp"

namespace stcache {
enum class CacheFileType : uint32_t {
  UnknownTextResource,
  GameInfo,
  Level,
  Instances,
  Resources,
  InstancesStatic,
  ShaderVertex,
  ShaderFragment,
  ShaderHlsl,
  UnknownBinaryResource,
  // Begin uncached data
  UnknownUncachedBinaryResource,
  Dds,
  Tga,
  Sbt,
  Sbm,
  Sba,
  Wav,
  // Begin streamed data
  Ogg,
  Avi,
};

inline bool IsBundled(CacheFileType type) {
  switch (type) {
  case CacheFileType::Instances:
  case CacheFileType::Resources:
  case CacheFileType::InstancesStatic:
    return true;
  default:
    return false;
  }

  return false;
}

inline bool IsVirtualSlak(CacheFileType type) {
  switch (type) {
  case CacheFileType::GameInfo:
  case CacheFileType::Level:
    return true;
  default:
    return false;
  }

  return false;
}

inline bool IsTextFile(CacheFileType type) {
  switch (type) {
  case CacheFileType::GameInfo:
  case CacheFileType::Level:
  case CacheFileType::UnknownTextResource:
    return true;
  default:
    return false;
  }

  return false;
}

inline bool IncludeExtension(CacheFileType type) {
  switch (type) {
  case CacheFileType::UnknownBinaryResource:
  case CacheFileType::UnknownUncachedBinaryResource:
  case CacheFileType::UnknownTextResource:
    return true;

  default:
    return false;
  }

  return false;
}

CacheFileType FromExtension(std::string_view ext);

template <class C> struct LocalArray {
  uint32_t numItems = 0;
  uint32_t pointer;

  const C *begin() const {
    return reinterpret_cast<const C *>(
        reinterpret_cast<const char *>(&pointer) + pointer);
  }
  const C *end() const { return begin() + numItems; }
  const C &operator[](size_t index) const { return begin()[index]; }

  C *begin() {
    return reinterpret_cast<C *>(reinterpret_cast<char *>(&pointer) + pointer);
  }
  C *end() { return begin() + numItems; }
  C &operator[](size_t index) { return begin()[index]; }
};

struct CacheFile {
  uint32_t nameHash;

  CacheFileType fileType : 5;
  uint32_t streamId : 9;
  uint32_t microOffset : 18; // BLOCK_SIZE

  uint32_t numBlocks : 14; // 4GiB
  uint32_t tailSize : 18;  // BLOCK_SIZE

  uint32_t blockOffset = 0; // Since reserved, act like 32bit
  // uint32_t blockOffset : 20; // 256GiB
  // uint32_t reserved : 12;
};

static_assert(sizeof(CacheFile) == 16);

struct CacheBlock {
  uint64_t offset;
  uint32_t size;
  uint32_t crc;
};

struct Cache {
  constexpr static uint32_t ID = 0x434d5453; // STMC
  uint32_t id = ID;
  uint16_t version = 1;
  uint16_t numVirtualLevels;
  uint16_t numGlobalResources;
  uint16_t numGlobalInstances;
  uint32_t uncachedBlocksBegin = -1;
  uint32_t streamingBlocksBegin = -1;
  LocalArray<CacheFile> files;
  LocalArray<CacheBlock> blocks;
  LocalArray<char> modName;
  LocalArray<char> author;
  LocalArray<char> modVersion;
  LocalArray<char> description;
  LocalArray<char> virtualLevels;
  LocalArray<char> globalResources;
  LocalArray<char> globalInstances;
};
} // namespace stcache
