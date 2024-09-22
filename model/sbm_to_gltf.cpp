/*  SBM2GLTF
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
#include "project.h"
#include "spike/app_context.hpp"
#include "spike/except.hpp"
#include "spike/gltf.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/reflect/reflector.hpp"
#include "spike/uni/model.hpp"
#include <set>

std::string_view filters[]{
    ".sbm$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .header = SBM2GLTF_DESC " v" SBM2GLTF_VERSION ", " SBM2GLTF_COPYRIGHT
                            "Lukas Cone",
    .filters = filters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct ReflectedInstanceFriend : ReflectedInstance {
  using ReflectedInstance::rfStatic;
};

struct Vertex64 {
  Vector position;
  Vector normal;
  UCVector4 color;
  Vector2 uv;
  Vector tangent;
  Vector4 unk;
};

static_assert(sizeof(Vertex64) == 64);

struct Vertex52 {
  Vector position;
  uint32 boneId;
  Vector normal;
  Vector2 uv;
  Vector tangent;
  float unk; // reflection?
};

static_assert(sizeof(Vertex52) == 52);

struct Vertex48 {
  Vector position;
  Vector normal;
  UCVector4 color;
  Vector2 uv;
  Vector tangent;
};

static_assert(sizeof(Vertex48) == 48);

struct Vertex24 {
  Vector position;
  Vector normal;
};

static_assert(sizeof(Vertex24) == 24);

struct Vertex28 {
  Vector position;
  uint32 boneId;
  Vector normal;
};

static_assert(sizeof(Vertex28) == 28);

struct Vertex20 {
  Vector position;
  Vector2 uv;
};

static_assert(sizeof(Vertex20) == 20);

std::span<const Attribute> Attributes(uint32 stride) {
  switch (stride) {
  case 64: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Normal,
        },
        {
            .type = uni::DataType::R8G8B8A8,
            .format = uni::FormatType::UNORM,
            .usage = AttributeType::VertexColor,
        },
        {
            .type = uni::DataType::R32G32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::TextureCoordiante,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Tangent,
        },
        {
            .type = uni::DataType::R32G32B32A32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Undefined,
        }};
    return ATTRS;
  }
  case 52: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32,
            .format = uni::FormatType::UINT,
            .usage = AttributeType::BoneIndices,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Normal,
        },
        {
            .type = uni::DataType::R32G32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::TextureCoordiante,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Tangent,
        },
        {
            .type = uni::DataType::R32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Undefined,
        }};

    return ATTRS;
  }
  case 48: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Normal,
        },
        {
            .type = uni::DataType::R8G8B8A8,
            .format = uni::FormatType::UNORM,
            .usage = AttributeType::VertexColor,
        },
        {
            .type = uni::DataType::R32G32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::TextureCoordiante,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Tangent,
        },
    };

    return ATTRS;
  }
  case 28: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32,
            .format = uni::FormatType::UINT,
            .usage = AttributeType::BoneIndices,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Normal,
        },
    };

    return ATTRS;
  }
  case 24: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Normal,
        },
    };

    return ATTRS;
  }
  case 20: {
    static const Attribute ATTRS[]{
        {
            .type = uni::DataType::R32G32B32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::Position,
        },
        {
            .type = uni::DataType::R32G32,
            .format = uni::FormatType::FLOAT,
            .usage = AttributeType::TextureCoordiante,
        },
    };

    return ATTRS;
  }
  default:
    throw std::runtime_error("Unknown vertex layout");
  }
}

void SaveLod(AppContext *ctx, SBM::Header &hdr, size_t lodIndex) {
  GLTFModel main;
  size_t renderNode = main.nodes.size();
  main.nodes.emplace_back().name = "Render";
  size_t volumeShadowNode = main.nodes.size();
  main.nodes.emplace_back().name = "ShadowCast";

  main.scenes.front().nodes.emplace_back(renderNode);
  main.scenes.front().nodes.emplace_back(volumeShadowNode);

  for (auto &m : hdr.materials) {
    auto reflMatInst = GetReflectedMaterial(m);
    ReflectorPureWrap reflMat(reflMatInst);
    auto &gMat = main.materials.emplace_back();
    gMat.name = reflMat["materialName"].ReflectedValue();
  }

  std::map<std::string, size_t> bones;
  size_t nodesBegin = main.nodes.size();
  main.scenes.front().nodes.emplace_back(nodesBegin);
  // main.transform = es::Matrix44{{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
  auto &model = hdr.lods.at(lodIndex);

  for (auto &b : model.bones) {
    bones.emplace(b.name, main.nodes.size());
    auto &cNode = main.nodes.emplace_back();
    cNode.name = b.name;
    for (auto &c : b.children) {
      cNode.children.emplace_back(c + nodesBegin);
    }

    memcpy(cNode.matrix.data(), &b.tm, sizeof(b.tm));
  }

  std::map<uint32, gltf::Attributes> mainOffsets;
  std::map<uint32, gltf::Attributes> shadowCastOffsets;
  std::map<uint32, uint32> skinRanges;

  for (auto &p : model.primitives) {
    if (p.name.starts_with("RawGeometry")) {
      continue;
    } else if (p.name.ends_with("_CompiledShadowShader")) {
      shadowCastOffsets.emplace(p.vertexBase, gltf::Attributes{});
    } else {
      mainOffsets.emplace(p.vertexBase, gltf::Attributes{});
    }

    if (p.boneOffset > 0) {
      uint32 &skn = skinRanges[p.boneOffset];
      skn = std::max(skn, p.numBones);
    }
  }

  for (auto &[off, size] : skinRanges) {
    auto &gSkin = main.skins.emplace_back();

    for (size_t i = 0; i < size; i++) {
      auto &joint = model.joints.at(off - 1 + i);
      size_t boneIndex = bones.at(joint.name);
      gSkin.joints.emplace_back(boneIndex);
    }

    size = main.skins.size() - 1;
  }

  auto MakeBufferSpan = [&main](auto &offsets, auto &buffer) {
    for (auto it = offsets.begin(); it != offsets.end(); it++) {
      auto nextIt = std::next(it);
      uint32 lastVertex =
          nextIt == offsets.end() ? buffer.numVertices : nextIt->first;
      uint32 numVertices = lastVertex - it->first;
      it->second = main.SaveVertices(
          buffer.vertexBuffer.data() + it->first * buffer.vertexStride,
          numVertices, Attributes(buffer.vertexStride), buffer.vertexStride);
    }
  };

  if (model.mainBuffer.numVertices) {
    MakeBufferSpan(mainOffsets, model.mainBuffer);
  }

  if (model.shadowCastBuffer.numVertices) {
    MakeBufferSpan(shadowCastOffsets, model.shadowCastBuffer);
  }

  if (model.bakedShadowBuffer.numVertices) {
    throw std::runtime_error("Shadow atlas is not supported");
  }

  auto MakePrimitive = [&main, &skinRanges](auto &offsets, SBM::Primitive &p,
                                            auto &buffer) {
    const size_t nodeIndex = main.nodes.size();
    {
      auto &mNode = main.nodes.emplace_back();
      mNode.mesh = main.meshes.size();
      if (skinRanges.size() > 0) {
        mNode.skin = skinRanges.at(p.boneOffset);
      }
    }

    auto &gMesh = main.meshes.emplace_back();

    gltf::Primitive &prim = gMesh.primitives.emplace_back();
    prim.attributes = offsets.at(p.vertexBase);
    prim.indices =
        main.SaveIndices(buffer.indexBuffer.data() + p.indexOffset * 2,
                         p.numIndices * 3)
            .accessorIndex;

    for (auto &m : main.materials) {
      if (m.name == p.materialName) {
        prim.material = std::distance(main.materials.data(), &m);
        break;
      }
    }

    return nodeIndex;
  };

  for (auto &p : model.primitives) {
    if (p.name.starts_with("RawGeometry")) {
      continue;
    } else if (p.name.ends_with("_CompiledShadowShader")) {
      size_t nodeId =
          MakePrimitive(shadowCastOffsets, p, model.shadowCastBuffer);
      main.nodes.at(volumeShadowNode).children.emplace_back(nodeId);
    } else {
      size_t nodeId = MakePrimitive(mainOffsets, p, model.mainBuffer);
      main.nodes.at(renderNode).children.emplace_back(nodeId);
    }
  }

  std::string lodId;
  if (lodIndex > 0) {
    lodId.append("lod" + std::to_string(lodIndex));
  }
  lodId.append(".glb");
  BinWritterRef wr(ctx->NewFile(ctx->workingFile.ChangeExtension(lodId)).str);

  main.FinishAndSave(wr, std::string(ctx->workingFile.GetFolder()));
}

void AppProcessFile(AppContext *ctx) {
  BinReaderRef rd(ctx->GetStream());
  SBM::Header hdr;
  rd.Read(hdr);

  for (size_t i = 0; i < hdr.lods.size(); i++) {
    SaveLod(ctx, hdr, i);
  }
}
