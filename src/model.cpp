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

#include "model.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include <cassert>

constexpr uint32 ID = CompileFourCC("SBM");

void SBM::Header::Read(BinReaderRef rd) {
  rd.Read(id);

  if (id != ID) {
    throw es::InvalidHeaderError(id);
  }

  rd.Read(versionMajor);
  rd.Read(versionMinor);

  rd.ReadContainerLambda(materials, ReadMaterialVariant);
  rd.Read(model);
}

void SBM::Header::Write(BinWritterRef rd) const {
  rd.Write(ID);
  rd.Write(versionMajor);
  rd.Write(versionMinor);

  rd.WriteContainerLambda(materials,
                          [](BinWritterRef wr, const MaterialVariant &mtr) {
                            std::visit([&](auto &mtl) { wr.Write(mtl); }, mtr);
                          });
  // rd.Write(model);
}

void SBM::Buffer::Read(BinReaderRef rd) {
  rd.Read(numVertices);
  rd.Read(vertexStride);
  rd.ReadContainer(vertexBuffer, numVertices * vertexStride);
  rd.Read(numFaces);
  rd.ReadContainer(indexBuffer);
}

void SBM::ShadowShader::Read(BinReaderRef rd) {
  rd.ReadString(shaderType);
  rd.ReadString(shaderName);
  rd.Read(unk0);
  rd.ReadString(shadowTexture);
  rd.Read(unk1);
}

void SBM::SkinBone::Read(BinReaderRef rd) {
  rd.Read(index);
  rd.Read(unk);
  rd.ReadString(name);
};

void SBM::Bone::Read(BinReaderRef rd) {
  rd.Read(tm);
  rd.Read(unk);
  rd.Read(hash);
  rd.ReadString(name);
};

void ReadBones(BinReaderRef rd, std::vector<SBM::Bone> &cnt,
               uint32 parentIndex) {
  uint32 numChildren;
  rd.Read(numChildren);
  int32 thisIndex = cnt.size();

  for (size_t i = 0; i < numChildren; i++) {
    cnt.at(parentIndex).children.emplace_back(cnt.size());
    rd.Read(cnt.emplace_back());
  }

  for (size_t i = 0; i < numChildren; i++) {
    ReadBones(rd, cnt, thisIndex + i);
  }
}

void SBM::RenderModel::Read(BinReaderRef rd) {
  rd.Read(modelType);
  rd.Read(mainBuffer);

  bool useShadowCaster;
  rd.Read(useShadowCaster);
  if (useShadowCaster) {
    rd.Read(shadowCastBuffer);
  }

  bool useShadowAtlas;
  rd.Read(useShadowAtlas);
  if (useShadowAtlas) {
    rd.Read(bakedShadowBuffer);
    rd.ReadContainer(shadowShaders);
  }

  rd.ReadContainer(primitives);
  rd.ReadContainer(ibms);
  rd.ReadContainer(nodeBounds);
  rd.ReadContainer(joints);
  int32 thisIndex = bones.size();
  rd.Read(bones.emplace_back());

  ReadBones(rd, bones, thisIndex);

  //rd.ReadContainer(lods);
}

void SBM::Primitive::Read(BinReaderRef rd) {
  rd.ReadString(name);
  rd.ReadString(materialName);
  rd.Read(numVertices);
  rd.Read(unk0);
  assert(unk0 == 4);
  rd.Read(numIndices);
  rd.Read(vertexBase);
  rd.Read(vertexOffset);
  rd.Read(indexOffset);
  rd.Read(numBones);
  rd.Read(boneOffset);
}
