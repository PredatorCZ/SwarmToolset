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

#include "terrain.hpp"
#include "spike/except.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"

constexpr uint32 ID = CompileFourCC("SBT");

void SBT::Header::Read(BinReaderRef rd) {
  rd.Read(id);

  if (id != ID) {
    throw es::InvalidHeaderError(id);
  }

  rd.Read(versionMajor);
  rd.Read(versionMinor);

  rd.ReadContainerLambda(materials, ReadMaterialVariant);
  rd.ReadContainer(groups);
  rd.ReadContainer(zones);
}

void SBT::Header::Write(BinWritterRef rd) const {
  rd.Write(ID);
  rd.Write(versionMajor);
  rd.Write(versionMinor);

  rd.WriteContainerLambda(materials,
                          [](BinWritterRef wr, const MaterialVariant &mtr) {
                            std::visit([&](auto &mtl) { wr.Write(mtl); }, mtr);
                          });
  rd.WriteContainerWCount(groups);
}

void SBT::Group::Read(BinReaderRef rd) {
  rd.ReadString(groupName);
  rd.ReadString(unkName);
  rd.ReadContainerLambda(
      usedMaterials, [](BinReaderRef rd, auto &str) { rd.ReadString(str); });
}

void SBT::Group::Write(BinWritterRef wr) const {
  wr.WriteT(groupName);
  wr.WriteT(unkName);
  wr.WriteContainerLambda(usedMaterials,
                          [](BinWritterRef wr, auto &str) { wr.WriteT(str); });
}

void SBT::ShadowShader::Read(BinReaderRef rd) {
  rd.ReadString(shaderType);
  rd.ReadString(shaderName);
  rd.Read(unk0);
  rd.ReadString(shadowTexture);
  rd.Read(unk1);
}

void SBT::Zone::Read(BinReaderRef rd) {
  rd.ReadString(name);
  rd.Read(bbox);
  rd.Read(unk0);
  rd.Read(shadowVolumeExtrusionDepth);
  rd.Read(model);
  rd.Read(collision);
}

void SBT::DepthField::Read(BinReaderRef rd) {
  rd.ReadString(depthMap);
  rd.Read(tm0);
  rd.Read(tm1);
  rd.Read(bbox);
}

constexpr uint32 BYOH = CompileFourCC("BYHO");

void SBT::CollisionObject::Read(BinReaderRef rd) {
  uint32 id;
  rd.Read(id);

  if (id != BYOH) {
    throw es::InvalidHeaderError(id);
  }

  rd.ReadContainer(ids0);
  uint32 numIds1;
  rd.Read(numIds1);

  if (numIds1 > 1) {
    rd.ReadContainer(ids1, numIds1);
  }

  rd.Read(unk3);
  if ((unk3 & 4) == 0) {
    rd.ReadContainer(bboxGroups);
  }
  uint32 numPositions;
  uint32 numTris;
  rd.Read(numPositions);
  rd.Read(numTris);
  rd.ReadContainer(positions, numPositions);
  rd.ReadContainer(tris, numTris);
  rd.ReadContainer(trisTypes, numTris);
  rd.Read(unk6);
  bool useDepthField;
  rd.Read(useDepthField);

  if (useDepthField) {
    rd.Read(depthField);
  }
}
