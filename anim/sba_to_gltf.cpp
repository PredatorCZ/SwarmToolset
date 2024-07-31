/*  SBA2GLTF
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
#include "spike/master_printer.hpp"
#include "spike/reflect/reflector.hpp"
#include "spike/uni/model.hpp"
#include <set>

std::string_view filters[]{
    ".sba$",
};

std::string_view controlFilters[]{
    ".glb$",
    ".gltf$",
};

static AppInfo_s appInfo{
    .filteredLoad = true,
    .header = SBA2GLTF_DESC " v" SBA2GLTF_VERSION ", " SBA2GLTF_COPYRIGHT
                            "Lukas Cone",
    .filters = filters,
    .batchControlFilters = controlFilters,
};

AppInfo_s *AppInitModule() { return &appInfo; }

struct GLTFAni : GLTF {
  using GLTF::GLTF;

  GLTFStream &AnimStream() {
    if (aniStream < 0) {
      auto &newStream = NewStream("anims");
      aniStream = newStream.slot;
      return newStream;
    }
    return Stream(aniStream);
  }

private:
  int32 aniStream = -1;
};

#include <cassert>

float ReadFrame(BinReaderRef rd) {
  uint16 frame;
  uint8 frac;
  rd.Read(frac);
  rd.Read(frame);
  uint8 null;
  rd.Read(null);

  assert(null == 0);

  return (frame + (1.f / 0xff) * frac) * (1.f / 30);
}

constexpr static uint32 ID = CompileFourCC("sba\0");

struct Track {
  std::vector<Vector4A16> values;
  std::vector<float> frames;
};

struct BoneAnim {
  std::string boneName;
  Track translations;
  Track rotations;
  Track scales;

  void Read(BinReaderRef rd) {
    uint64 boneHash;
    rd.Read(boneHash);
    rd.ReadString(boneName);

    auto LoadVector3 = [&](Track &track) {
      uint32 numItems;
      rd.Read(numItems);

      for (uint32 i = 0; i < numItems; i++) {
        Vector value;
        rd.Read(value);
        track.values.emplace_back(value);
        track.frames.emplace_back(ReadFrame(rd));
      }
    };

    LoadVector3(scales);

    uint32 numItems;
    rd.Read(numItems);

    for (uint32 i = 0; i < numItems; i++) {
      rd.Read(rotations.values.emplace_back());
      rotations.frames.emplace_back(ReadFrame(rd));
    }

    LoadVector3(translations);
  }
};

void LoadAnim(GLTFAni &main, std::istream &str, std::string name) {
  BinReaderRef rd(str);
  uint32 id;
  rd.Read(id);

  if (id != ID) {
    throw es::InvalidHeaderError(id);
  }

  uint16 version;
  rd.Read(version);

  if (version != 0x3531) {
    throw es::InvalidVersionError(version);
  }

  float maxFrame = ReadFrame(rd);

  std::vector<BoneAnim> anims;
  rd.ReadContainer(anims);

  gltf::Animation &gAnim = main.animations.emplace_back();
  gAnim.name = name;

  for (auto &anim : anims) {
    int32 nodeId = -1;
    for (int32 id = -1; auto node : main.nodes) {
      id++;
      if (node.name == anim.boneName) {
        nodeId = id;
        break;
      }
    }

    if (nodeId < 0) {
      PrintWarning("Cannot find node: ", anim.boneName);
      continue;
    }

    auto SaveVector3 = [&](const std::string &path, Track &track) {
      gltf::Animation::Channel &channel = gAnim.channels.emplace_back();
      channel.target.node = nodeId;
      channel.target.path = path;
      channel.sampler = gAnim.samplers.size();
      auto &sampler = gAnim.samplers.emplace_back();

      auto &stream = main.AnimStream();
      {
        auto [acc, accid] = main.NewAccessor(stream, 4);
        acc.componentType = gltf::Accessor::ComponentType::Float;
        acc.type = gltf::Accessor::Type::Vec3;
        acc.count = track.values.size();
        sampler.output = accid;

        for (auto v : track.values) {
          stream.wr.Write<Vector>(v);
        }
      }

      {
        auto [acc, accid] = main.NewAccessor(stream, 4);
        acc.componentType = gltf::Accessor::ComponentType::Float;
        acc.type = gltf::Accessor::Type::Scalar;
        acc.count = track.values.size();
        sampler.input = accid;

        stream.wr.WriteContainer(track.frames);
      }
    };

    if (anim.rotations.frames.size() > 0) {
      gltf::Animation::Channel &channel = gAnim.channels.emplace_back();
      channel.target.node = nodeId;
      channel.target.path = "rotation";
      channel.sampler = gAnim.samplers.size();
      auto &sampler = gAnim.samplers.emplace_back();

      auto &stream = main.AnimStream();
      {
        auto [acc, accid] = main.NewAccessor(stream, 2);
        acc.componentType = gltf::Accessor::ComponentType::Short;
        acc.type = gltf::Accessor::Type::Vec4;
        acc.normalized = true;
        acc.count = anim.rotations.values.size();
        sampler.output = accid;

        for (auto value : anim.rotations.values) {
          value *= 0x7fff;
          value = Vector4A16(_mm_round_ps(value._data, _MM_ROUND_NEAREST));
          stream.wr.Write(value.Convert<int16>());
        }
      }

      {
        auto [acc, accid] = main.NewAccessor(stream, 4);
        acc.componentType = gltf::Accessor::ComponentType::Float;
        acc.type = gltf::Accessor::Type::Scalar;
        acc.count = anim.rotations.values.size();
        sampler.input = accid;

        stream.wr.WriteContainer(anim.rotations.frames);
      }
    }

    if (anim.translations.frames.size() > 0) {
      SaveVector3("translation", anim.translations);
    }

    if (anim.scales.frames.size() > 0) {
      SaveVector3("scale", anim.scales);
    }
  }
}

void AppProcessFile(AppContext *ctx) {
  GLTFAni main(gltf::LoadFromBinary(ctx->GetStream(), ""));
  auto &anims = ctx->SupplementalFiles();

  for (auto &animFile : anims) {
    auto animStream = ctx->RequestFile(animFile);
    LoadAnim(main, *animStream.Get(), std::string(AFileInfo(animFile).GetFilename()));
  }

  BinWritterRef wr(
      ctx->NewFile(std::string(ctx->workingFile.GetFullPathNoExt()) +
                   "_out.glb")
          .str);
  main.FinishAndSave(wr, std::string(ctx->workingFile.GetFolder()));
}
