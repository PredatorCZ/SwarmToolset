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
#include "material.hpp"
#include "spike/io/bincore_fwd.hpp"
#include <vector>

namespace SBT {
struct Group {
  std::string groupName;
  std::string unkName;
  std::vector<std::string> usedMaterials;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Zone {};

struct Header {
  uint32 id;
  uint8 versionMajor;
  uint8 versionMinor;

  std::vector<MaterialVariant> materials;
  std::vector<Group> groups;
  std::vector<Zone> zones;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};
} // namespace SBT
