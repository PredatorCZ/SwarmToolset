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
#include "spike/type/matrix44.hpp"
#include <vector>

namespace SBM {
struct Buffer {
  uint32 numVertices;
  uint32 vertexStride;
  std::string vertexBuffer;
  uint32 numFaces;
  std::string indexBuffer;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct BBOX {
  Vector min;
  Vector max;
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

struct Primitive {
  std::string name;
  std::string materialName;
  uint32 numVertices;
  uint32 unk0;
  uint32 numIndices;
  uint32 vertexBase;
  uint32 vertexOffset;
  uint32 indexOffset;
  uint32 numBones;
  uint32 boneOffset;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct SkinBone {
  uint32 index;
  uint32 unk;
  std::string name;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Bone {
  es::Matrix44 tm;
  std::vector<uint32> children;
  uint32 unk;
  uint64 hash;
  std::string name;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct RenderModel {
  uint8 modelType;
  Buffer mainBuffer{};
  Buffer shadowCastBuffer{};
  Buffer bakedShadowBuffer{};
  std::vector<ShadowShader> shadowShaders;
  std::vector<Primitive> primitives;
  std::vector<es::Matrix44> ibms;
  std::vector<BBOX> nodeBounds;
  std::vector<SkinBone> joints;
  std::vector<Bone> bones;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Header {
  uint32 id;
  uint8 versionMajor;
  uint8 versionMinor;

  std::vector<MaterialVariant> materials;
  std::vector<RenderModel> lods;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};
} // namespace SBM
