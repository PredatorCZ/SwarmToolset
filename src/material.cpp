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

#include "material.hpp"
#include "spike/io/binreader_stream.hpp"
#include "spike/io/binwritter_stream.hpp"
#include "spike/reflect/reflector.hpp"
#include <map>

enum class ShaderType {
  Phong,
  BumpTexBlend2,
  Anisotropic,
  Unlit,
  Glow,
  TintDistort,
  Overlay,
};

template <class C> MaterialVariant ReadMaterial(BinReaderRef rd) {
  C mtl;
  rd.Read(mtl);
  return mtl;
}

std::map<ShaderType, MaterialVariant (*)(BinReaderRef)> MTLREAD{
    {ShaderType::Anisotropic, ReadMaterial<BumpAnisotropic>},
    {ShaderType::Glow, ReadMaterial<Glow>},
    {ShaderType::Unlit, ReadMaterial<Unlit>},
    {ShaderType::Phong, ReadMaterial<BumpSpecular>},
    {ShaderType::BumpTexBlend2, ReadMaterial<BumpTexBlend2>},
    {ShaderType::Overlay, ReadMaterial<Overlay>},
    {ShaderType::TintDistort, ReadMaterial<TintDistort>},

};

void ReadMaterialVariant(BinReaderRef rd, MaterialVariant &mtr) {
  ShaderType shaderType;
  rd.Read(shaderType);

  mtr = MTLREAD.at(shaderType)(rd);
}

void Material::Read(BinReaderRef rd) {
  rd.ReadString(materialName);
  rd.ReadString(resourceGUID);
  rd.ReadString(shaderTypeName);
  rd.ReadString(renShaderName);
  uint32 constValue;
  rd.Read(constValue); // always 5
}

void BumpAnisotropic::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.ReadString(anisotropyTexture);
  rd.Read(ambient);
  rd.Read(diffuse);
  rd.Read(specular);
  rd.Read(unk1);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(alphaTested);
  rd.Read(blended);
  rd.Read(doubleFaced);
  rd.Read(ignoreMipMaps);
  rd.Read(unk);
}

void Glow::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.ReadString(glowTexture);
  rd.Read(glowUVScale);
  rd.Read(glowUVOffset);
  rd.Read(velocity);
  rd.Read(glowLevel);
  rd.Read(glowFactor);
  rd.Read(blended);
  rd.Read(fogFactor);
}

void RenMaterial::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.Read(diffuse);
  rd.Read(ambient);
  rd.Read(specular);
  rd.Read(unk1);
  rd.Read(unk2);
  rd.Read(generateShadows);
  rd.Read(alphaBlended);
  rd.Read(alphaTested);
  rd.Read(srcBlend);
  rd.Read(destBlend);
}

void Unlit::Read(BinReaderRef rd) {
  RenMaterial::Read(rd);
  rd.ReadString(albedoTexture);
  rd.Read(pulseFrequency);
  rd.Read(pulseSeed);
  rd.Read(pulseOffset);
  rd.Read(velocity);
  rd.Read(textureUVOffset);
  rd.Read(unk0);
  rd.Read(fogOutFactor);
  rd.Read(blended);
  rd.Read(fogFactor);
  rd.Read(vertexAlpha);
}

void BumpSpecular::Read(BinReaderRef rd) {
  RenMaterial::Read(rd);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(albedoUVOffset);
  rd.Read(normalUVOffset);
  rd.Read(blended);
  rd.Read(doubleFaced);
  rd.Read(ignoreMipMaps);
  rd.Read(unk);
}

void BumpTexBlend2::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.ReadString(alebedo0Texture);
  rd.ReadString(alebedo1Texture);
  rd.ReadString(normalTexture);
  rd.Read(ambient);
  rd.Read(diffuse);
  rd.Read(specular);
  rd.Read(unk1);
  rd.Read(texture1Scale);
  rd.Read(texture2Scale);
  rd.Read(texture3Scale);
  rd.Read(unk2);
  rd.Read(applyNormalTo1stTextureOnly);
  rd.Read(unk3);
}

void Overlay::Read(BinReaderRef rd) {
  RenMaterial::Read(rd);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(albedoUVOffset);
  rd.Read(normalUVOffset);
  rd.Read(textureVelocity);
  rd.Read(depthBias);
  rd.Read(blended);
  rd.Read(vertexAlpha);
}

void TintDistort::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.ReadString(tintTexture);
  rd.ReadString(distortlTexture);
  rd.Read(ambient);
  rd.Read(velocity);
  rd.Read(textureUVOffset);
  rd.Read(unk);
  rd.Read(blended);
}

void Material::Write(BinWritterRef rd) const {
  rd.WriteT(materialName);
  rd.WriteT(resourceGUID);
  rd.WriteT(shaderTypeName);
  rd.WriteT(renShaderName);
  rd.Write(5);
}

void BumpAnisotropic::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::Anisotropic);
  Material::Write(rd);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.WriteT(anisotropyTexture);
  rd.Write(ambient);
  rd.Write(diffuse);
  rd.Write(specular);
  rd.Write(unk1);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(alphaTested);
  rd.Write(blended);
  rd.Write(doubleFaced);
  rd.Write(ignoreMipMaps);
  rd.Write(unk);
}

void Glow::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::Glow);
  Material::Write(rd);
  rd.WriteT(glowTexture);
  rd.Write(glowUVScale);
  rd.Write(glowUVOffset);
  rd.Write(velocity);
  rd.Write(glowLevel);
  rd.Write(glowFactor);
  rd.Write(blended);
  rd.Write(fogFactor);
}

void RenMaterial::Write(BinWritterRef rd) const {
  Material::Write(rd);
  rd.Write(diffuse);
  rd.Write(ambient);
  rd.Write(specular);
  rd.Write(unk1);
  rd.Write(unk2);
  rd.Write(generateShadows);
  rd.Write(alphaBlended);
  rd.Write(alphaTested);
  rd.Write(srcBlend);
  rd.Write(destBlend);
}

void Unlit::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::Unlit);
  RenMaterial::Write(rd);
  rd.WriteT(albedoTexture);
  rd.Write(pulseFrequency);
  rd.Write(pulseSeed);
  rd.Write(pulseOffset);
  rd.Write(velocity);
  rd.Write(textureUVOffset);
  rd.Write(unk0);
  rd.Write(fogOutFactor);
  rd.Write(blended);
  rd.Write(fogFactor);
  rd.Write(vertexAlpha);
}

void BumpSpecular::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::Phong);
  RenMaterial::Write(rd);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(albedoUVOffset);
  rd.Write(normalUVOffset);
  rd.Write(blended);
  rd.Write(doubleFaced);
  rd.Write(ignoreMipMaps);
  rd.Write(unk);
}

void BumpTexBlend2::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::BumpTexBlend2);
  Material::Write(rd);
  rd.WriteT(alebedo0Texture);
  rd.WriteT(alebedo1Texture);
  rd.WriteT(normalTexture);
  rd.Write(ambient);
  rd.Write(diffuse);
  rd.Write(specular);
  rd.Write(unk1);
  rd.Write(texture1Scale);
  rd.Write(texture2Scale);
  rd.Write(texture3Scale);
  rd.Write(unk2);
  rd.Write(applyNormalTo1stTextureOnly);
  rd.Write(unk3);
}

void Overlay::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::Overlay);
  RenMaterial::Write(rd);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(albedoUVOffset);
  rd.Write(normalUVOffset);
  rd.Write(textureVelocity);
  rd.Write(depthBias);
  rd.Write(blended);
  rd.Write(vertexAlpha);
}

void TintDistort::Write(BinWritterRef rd) const {
  rd.Write(ShaderType::TintDistort);
  Material::Write(rd);
  rd.WriteT(tintTexture);
  rd.WriteT(distortlTexture);
  rd.Write(ambient);
  rd.Write(velocity);
  rd.Write(textureUVOffset);
  rd.Write(unk);
  rd.Write(blended);
}

REFLECT(CLASS(Material), MEMBER(materialName), MEMBER(resourceGUID),
        MEMBER(shaderTypeName), MEMBER(renShaderName))

REFLECT(BASEDCLASS(Material, RenMaterial), MEMBER(diffuse), MEMBER(ambient),
        MEMBER(specular), MEMBER(unk1), MEMBER(unk2), MEMBER(generateShadows),
        MEMBER(alphaBlended), MEMBER(alphaTested), MEMBER(srcBlend),
        MEMBER(destBlend));

REFLECT(BASEDCLASS(Material, BumpAnisotropic), MEMBER(alebedoTexture),
        MEMBER(normalTexture), MEMBER(anisotropyTexture), MEMBER(ambient),
        MEMBER(diffuse), MEMBER(specular), MEMBER(unk1), MEMBER(albedoUVScale),
        MEMBER(normalUVScale), MEMBER(alphaTested), MEMBER(blended),
        MEMBER(doubleFaced), MEMBER(ignoreMipMaps), MEMBER(unk))

REFLECT(BASEDCLASS(Material, Glow), MEMBER(glowTexture), MEMBER(glowUVScale),
        MEMBER(glowUVOffset), MEMBER(velocity), MEMBER(glowLevel),
        MEMBER(glowFactor), MEMBER(blended), MEMBER(fogFactor))

REFLECT(BASEDCLASS(RenMaterial, Unlit), MEMBER(albedoTexture),
        MEMBER(pulseFrequency), MEMBER(pulseSeed), MEMBER(pulseOffset),
        MEMBER(velocity), MEMBER(textureUVOffset), MEMBER(unk0),
        MEMBER(fogOutFactor), MEMBER(blended), MEMBER(fogFactor),
        MEMBER(vertexAlpha))

REFLECT(BASEDCLASS(RenMaterial, BumpSpecular), MEMBER(alebedoTexture),
        MEMBER(normalTexture), MEMBER(albedoUVScale), MEMBER(normalUVScale),
        MEMBER(albedoUVOffset), MEMBER(normalUVOffset), MEMBER(blended),
        MEMBER(doubleFaced), MEMBER(ignoreMipMaps), MEMBER(unk))

REFLECT(BASEDCLASS(Material, BumpTexBlend2), MEMBER(alebedo0Texture),
        MEMBER(alebedo1Texture), MEMBER(normalTexture), MEMBER(ambient),
        MEMBER(diffuse), MEMBER(specular), MEMBER(unk1), MEMBER(texture1Scale),
        MEMBER(texture2Scale), MEMBER(texture3Scale), MEMBER(unk2),
        MEMBER(applyNormalTo1stTextureOnly), MEMBER(unk3))

REFLECT(BASEDCLASS(RenMaterial, Overlay), MEMBER(alebedoTexture),
        MEMBER(normalTexture), MEMBER(albedoUVScale), MEMBER(normalUVScale),
        MEMBER(albedoUVOffset), MEMBER(normalUVOffset), MEMBER(textureVelocity),
        MEMBER(depthBias), MEMBER(blended), MEMBER(vertexAlpha))

REFLECT(BASEDCLASS(Material, TintDistort), MEMBER(tintTexture),
        MEMBER(distortlTexture), MEMBER(ambient), MEMBER(velocity),
        MEMBER(textureUVOffset), MEMBER(unk), MEMBER(blended))

ReflectedInstance GetReflectedMaterial(MaterialVariant &mtr) {
  return std::visit(
      [](auto &data) {
        using MType = std::decay_t<decltype(data)>;

        return ReflectedInstance(GetReflectedClass<MType>(), &data);
      },
      mtr);
}
