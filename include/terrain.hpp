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
#include "model.hpp"

namespace SBT {
struct Group {
  std::string groupName;
  std::string unkName;
  std::vector<std::string> usedMaterials;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct ShadowShader {
  std::string shaderType;
  std::string shaderName;
  uint32 unk0;
  std::string shadowTexture;
  float unk1[4];

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct DepthField {
  std::string depthMap;
  es::Matrix44 tm0;
  es::Matrix44 tm1;
  SBM::BBOX bbox;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct CollisionBBoxGroup {
  SBM::BBOX bbox;
  uint32 unk4[2];
};

struct CollisionObject {
  std::vector<uint32> ids0;
  std::vector<uint32> ids1;
  uint32 unk3;

  std::vector<CollisionBBoxGroup> bboxGroups;
  std::vector<Vector> positions;
  std::vector<IVector> tris;
  std::vector<uint32> trisTypes;

  float unk6[10];

  DepthField depthField;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Zone {
  std::string name;
  SBM::BBOX bbox;
  bool unk0[2];
  float shadowVolumeExtrusionDepth;
  SBM::RenderModel model;
  CollisionObject collision;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

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
