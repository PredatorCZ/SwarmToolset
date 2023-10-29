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

struct DescProxy : uni::PrimitiveDescriptor {
  const char *buffer;
  size_t stride;
  size_t offset = 0;
  size_t index = 0;
  Usage_e usage;
  uni::FormatDescr type;

  const char *RawBuffer() const override { return buffer; }
  size_t Stride() const override { return stride; }
  size_t Offset() const override { return offset; }
  size_t Index() const override { return index; }
  Usage_e Usage() const override { return usage; }
  uni::FormatDescr Type() const override { return type; }
  uni::BBOX UnpackData() const override { return {}; }
  UnpackDataType_e UnpackDataType() const override {
    return UnpackDataType_e::None;
  }
};

gltf::Attributes MakeBuffer(std::span<Vertex64> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 64;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Normal;
  proxy.buffer += 12;
  attrs["NORMAL"] = main.WriteNormals16(proxy, vtSpan.size());

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vertex52> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 52;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Normal;
  proxy.buffer += 16;
  attrs["NORMAL"] = main.WriteNormals16(proxy, vtSpan.size());

  auto &stream = main.GetVt4();
  {
    auto [acc, index] = main.NewAccessor(stream, 4);
    acc.count = vtSpan.size();
    acc.componentType = gltf::Accessor::ComponentType::UnsignedByte;
    acc.type = gltf::Accessor::Type::Vec4;
    attrs["JOINTS_0"] = index;

    for (auto &v : vtSpan) {
      stream.wr.Write(v.boneId);
    }
  }

  {
    // todo make only one buffer
    auto [acc, index] = main.NewAccessor(stream, 4);
    acc.count = vtSpan.size();
    acc.componentType = gltf::Accessor::ComponentType::UnsignedByte;
    acc.normalized = true;
    acc.type = gltf::Accessor::Type::Vec4;
    attrs["WEIGHTS_0"] = index;

    for (auto &v : vtSpan) {
      stream.wr.Write(0xff);
    }
  }

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vertex48> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 48;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Normal;
  proxy.buffer += 12;
  attrs["NORMAL"] = main.WriteNormals16(proxy, vtSpan.size());

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vertex28> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 28;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Normal;
  proxy.buffer += 16;
  attrs["NORMAL"] = main.WriteNormals16(proxy, vtSpan.size());

  auto &stream = main.GetVt4();
  {
    auto [acc, index] = main.NewAccessor(stream, 4);
    acc.count = vtSpan.size();
    acc.componentType = gltf::Accessor::ComponentType::UnsignedByte;
    acc.type = gltf::Accessor::Type::Vec4;
    attrs["JOINTS_0"] = index;

    for (auto &v : vtSpan) {
      stream.wr.Write(v.boneId);
    }
  }

  {
    // todo make only one buffer
    auto [acc, index] = main.NewAccessor(stream, 4);
    acc.count = vtSpan.size();
    acc.componentType = gltf::Accessor::ComponentType::UnsignedByte;
    acc.normalized = true;
    acc.type = gltf::Accessor::Type::Vec4;
    attrs["WEIGHTS_0"] = index;

    for (auto &v : vtSpan) {
      stream.wr.Write(0xff);
    }
  }

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vertex24> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 24;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Normal;
  proxy.buffer += 12;
  attrs["NORMAL"] = main.WriteNormals16(proxy, vtSpan.size());

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vertex20> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 20;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  proxy.usage = uni::PrimitiveDescriptor::Usage_e::TextureCoordiante;
  proxy.buffer += 12;
  proxy.type.compType = uni::DataType::R32G32;
  main.WriteTexCoord(attrs, proxy, vtSpan.size());

  return attrs;
}

gltf::Attributes MakeBuffer(std::span<Vector> vtSpan, GLTFModel &main) {
  DescProxy proxy;
  proxy.buffer = reinterpret_cast<const char *>(vtSpan.data());
  proxy.stride = 12;
  proxy.usage = uni::PrimitiveDescriptor::Usage_e::Position;
  proxy.type =
      uni::FormatDescr{uni::FormatType::FLOAT, uni::DataType::R32G32B32};

  gltf::Attributes attrs;
  main.WritePositions(attrs, proxy, vtSpan.size());

  return attrs;
}

struct IndexProxy : uni::IndexArray {
  const char *buffer;
  size_t numIndices;
  size_t indexSize = 2;

  const char *RawIndexBuffer() const override { return buffer; }
  size_t IndexSize() const override { return indexSize; }
  size_t NumIndices() const override { return numIndices; }
};

gltf::Attributes AddBuffer(SBM::Buffer &buffer, GLTFModel &main,
                           uint32 vertexBase, uint32 numVertices) {
  gltf::Attributes attributes;

  switch (buffer.vertexStride) {
  case 64: {
    std::span<Vertex64> vtSpan(
        reinterpret_cast<Vertex64 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  case 52: {
    std::span<Vertex52> vtSpan(
        reinterpret_cast<Vertex52 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  case 48: {
    std::span<Vertex48> vtSpan(
        reinterpret_cast<Vertex48 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  case 28: {
    std::span<Vertex28> vtSpan(
        reinterpret_cast<Vertex28 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  case 24: {
    std::span<Vertex24> vtSpan(
        reinterpret_cast<Vertex24 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  case 20: {
    std::span<Vertex20> vtSpan(
        reinterpret_cast<Vertex20 *>(buffer.vertexBuffer.data()) + vertexBase,
        numVertices);
    attributes = MakeBuffer(vtSpan, main);
    break;
  }
  default:
    throw std::runtime_error("Unknown vertex layout");
  }

  return attributes;
}

void AppProcessFile(AppContext *ctx) {
  BinReaderRef rd(ctx->GetStream());
  SBM::Header hdr;
  rd.Read(hdr);

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
    gMat.name = reflMat.GetReflectedValue("materialName");
  }

  std::map<std::string, size_t> bones;
  size_t nodesBegin = main.nodes.size();
  main.scenes.front().nodes.emplace_back(nodesBegin);
  //main.transform = es::Matrix44{{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};

  for (auto &b : hdr.model.bones) {
    bones.emplace(b.name, main.nodes.size());
    auto &cNode = main.nodes.emplace_back();
    cNode.name = b.name;
    for (auto &c : b.children) {
      cNode.children.emplace_back(c + nodesBegin);
    }

    memcpy(cNode.matrix.data(), &b.tm, sizeof(b.tm));
  }

  auto &mesh = hdr.model;
  std::map<uint32, gltf::Attributes> mainOffsets;
  std::map<uint32, gltf::Attributes> shadowCastOffsets;
  std::map<uint32, uint32> skinRanges;

  for (auto &p : mesh.primitives) {
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
      auto &joint = hdr.model.joints.at(off - 1 + i);
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
      it->second = AddBuffer(buffer, main, it->first, numVertices);
    }
  };

  if (mesh.mainBuffer.numVertices) {
    MakeBufferSpan(mainOffsets, mesh.mainBuffer);
  }

  if (mesh.shadowCastBuffer.numVertices) {
    MakeBufferSpan(shadowCastOffsets, mesh.shadowCastBuffer);
  }

  if (mesh.bakedShadowBuffer.numVertices) {
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

    IndexProxy iProxy;
    iProxy.buffer = buffer.indexBuffer.data() + p.indexOffset * 2;
    iProxy.numIndices = p.numIndices * 3;
    prim.indices = main.SaveIndices(iProxy);

    for (auto &m : main.materials) {
      if (m.name == p.materialName) {
        prim.material = std::distance(main.materials.data(), &m);
        break;
      }
    }

    return nodeIndex;
  };

  for (auto &p : mesh.primitives) {
    if (p.name.starts_with("RawGeometry")) {
      continue;
    } else if (p.name.ends_with("_CompiledShadowShader")) {
      size_t nodeId =
          MakePrimitive(shadowCastOffsets, p, mesh.shadowCastBuffer);
      main.nodes.at(volumeShadowNode).children.emplace_back(nodeId);
    } else {
      size_t nodeId = MakePrimitive(mainOffsets, p, mesh.mainBuffer);
      main.nodes.at(renderNode).children.emplace_back(nodeId);
    }
  }

  main.extensionsRequired.emplace_back("KHR_mesh_quantization");
  main.extensionsUsed.emplace_back("KHR_mesh_quantization");
  BinWritterRef wr(ctx->NewFile(ctx->workingFile.ChangeExtension2("glb")).str);

  main.FinishAndSave(wr, std::string(ctx->workingFile.GetFolder()));
}
