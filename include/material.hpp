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
#include "spike/io/bincore_fwd.hpp"
#include "spike/type/vectors.hpp"
#include "spike/util/supercore.hpp"
#include <variant>

struct ReflectedInstance;

struct Material {
  std::string materialName;
  std::string resourceGUID;
  std::string shaderTypeName;
  std::string renShaderName;

  void ReflectorTag();
  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct BumpAnisotropic : Material {
  std::string alebedoTexture;
  std::string normalTexture;
  std::string anisotropyTexture;
  Vector4 ambient;
  Vector4 diffuse;
  Vector4 specular;
  float unk1[5]; // unused
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  bool alphaTested;
  bool blended;
  bool doubleFaced;
  bool ignoreMipMaps;
  bool unk;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Glow : Material {
  std::string glowTexture;
  Vector2 glowUVScale;
  Vector2 glowUVOffset; // runtime
  Vector2 velocity;
  float glowLevel;
  float glowFactor;
  bool blended;
  float fogFactor;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct RenMaterial : Material {
  Vector4 diffuse;
  Vector4 ambient;
  Vector4 specular;
  Vector4 unk1;
  float unk2;
  bool generateShadows;
  bool alphaBlended;
  bool alphaTested;
  uint32 srcBlend;
  uint32 destBlend;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Unlit : RenMaterial {
  std::string albedoTexture;
  float pulseFrequency;
  float pulseSeed; // runtime
  float pulseOffset; // runtime
  Vector2 velocity;
  Vector2 textureUVOffset; // runtime
  Vector2 unk0;
  float fogOutFactor;
  bool blended;
  float fogFactor;
  bool vertexAlpha;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct BumpSpecular : RenMaterial {
  std::string alebedoTexture;
  std::string normalTexture;
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  Vector2 albedoUVOffset;
  Vector2 normalUVOffset;
  bool blended;
  bool doubleFaced;
  bool ignoreMipMaps;
  bool unk;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct BumpTexBlend2 : Material {
  std::string alebedo0Texture;
  std::string alebedo1Texture;
  std::string normalTexture;
  Vector4 ambient;
  Vector4 diffuse;
  Vector4 specular;
  float unk1[5];
  float texture1Scale;
  float texture2Scale;
  float texture3Scale;
  float unk2;
  bool applyNormalTo1stTextureOnly;
  bool unk3;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Overlay : RenMaterial {
  std::string alebedoTexture;
  std::string normalTexture;
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  Vector2 albedoUVOffset;
  Vector2 normalUVOffset;
  Vector2 textureVelocity;
  uint32 depthBias;
  bool blended;
  bool vertexAlpha;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct TintDistort : Material {
  std::string tintTexture;
  std::string distortlTexture;
  Vector4 ambient;
  Vector2 velocity;
  Vector2 textureUVOffset;
  Vector2 unk;
  bool blended;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

using MaterialVariant = std::variant<BumpAnisotropic, Glow, Unlit, BumpSpecular,
                                     BumpTexBlend2, Overlay, TintDistort>;

void ReadMaterialVariant(BinReaderRef rd, MaterialVariant &mtr);

ReflectedInstance GetReflectedMaterial(MaterialVariant &mtr);
