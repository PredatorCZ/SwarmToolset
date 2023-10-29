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
  uint32 unk;
  std::string meshName;
  std::string materialName;
  std::string shaderType;
  std::string shaderName;
  uint32 unk0;

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
  float unk1[5];
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  bool masked;
  uint32 blended;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Glow : Material {
  std::string glowTexture;
  Vector2 glowUVScale;
  Vector2 glowUVOffset; // ??
  Vector2 velocity;     // ??
  float glowLevel;
  float glowFactor;
  bool blended;
  float fogFactor;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct Unlit : Material {
  Vector4 ambient;
  Vector4 diffuse;
  uint8 unk1[36];
  bool generatedShadows;
  bool translucent;
  uint8 null0;
  uint8 unk2[8];
  std::string albedoTexture;
  float pulseFrequency;
  uint8 unk3[8];
  float velocity[2];
  uint8 unk4[16];
  float fogFactor;
  bool blended;
  float fogOutFactor;
  bool vertexAlpha;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct BumpSpecular : Material {
  Vector4 ambient;
  Vector4 diffuse;
  Vector4 specular;
  float unk1[5];
  bool generatedShadows;
  bool translucent;
  bool masked;
  uint8 unk2[8];
  std::string alebedoTexture;
  std::string normalTexture;
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  Vector2 albedoUVOffset;
  Vector2 normalUVOffset;
  uint32 blended;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct TexBlend : Material {
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

struct Overlay : Material {
  Vector4 ambient;
  Vector4 diffuse;
  Vector4 specular;
  float unk1[5];
  bool vertexAlpha;
  uint8 unk2[2];
  uint32 unk3[2];
  std::string alebedoTexture;
  std::string normalTexture;
  Vector2 albedoUVScale;
  Vector2 normalUVScale;
  Vector2 albedoUVOffset;
  Vector2 normalUVOffset;
  Vector2 textureVelocity;
  uint32 depthBias;
  bool isBlended;
  uint8 data2;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

struct TintDistort : Material {
  std::string alebedoTexture;
  std::string normalTexture;
  Vector2 albedoUVScale;   // ??
  Vector2 normalUVScale;   // ??
  Vector2 albedoUVOffset;  // ??
  Vector2 normalUVOffset;  // ??
  Vector2 textureVelocity; // ??
  bool isBlended;

  void Read(BinReaderRef rd);
  void Write(BinWritterRef wr) const;
};

using MaterialVariant = std::variant<BumpAnisotropic, Glow, Unlit, BumpSpecular,
                                     TexBlend, Overlay, TintDistort>;

void ReadMaterialVariant(BinReaderRef rd, MaterialVariant &mtr);

ReflectedInstance GetReflectedMaterial(MaterialVariant &mtr);
