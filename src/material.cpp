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

template <class C> MaterialVariant ReadMaterial(BinReaderRef rd) {
  C mtl;
  rd.Read(mtl);
  return mtl;
}

std::map<std::string_view, MaterialVariant (*)(BinReaderRef)> MTLREAD{
    {"BumpAnisotropic", ReadMaterial<BumpAnisotropic>},
    {"Glow", ReadMaterial<Glow>},
    {"Unlit", ReadMaterial<Unlit>},
    {"BumpSpecular", ReadMaterial<BumpSpecular>},
    {"TexBlend", ReadMaterial<TexBlend>},
    {"Overlay", ReadMaterial<Overlay>},
    {"TintDistort", ReadMaterial<TintDistort>},

};

void ReadMaterialVariant(BinReaderRef rd, MaterialVariant &mtr) {
  Material base;
  rd.Push();
  rd.Read(base);
  rd.Pop();
  std::string_view shaderName(base.shaderType);

  if (shaderName.ends_with("_Blended")) {
    shaderName.remove_suffix(8);
  }

  mtr = MTLREAD.at(shaderName)(rd);
}

void Material::Read(BinReaderRef rd) {
  rd.Read(unk);
  rd.ReadString(meshName);
  rd.ReadString(materialName);
  rd.ReadString(shaderType);
  rd.ReadString(shaderName);
  rd.Read(unk0);
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
  rd.Read(masked);
  rd.Read(blended);
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

void Unlit::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.Read(ambient);
  rd.Read(diffuse);
  rd.Read(unk1);
  rd.Read(generatedShadows);
  rd.Read(translucent);
  rd.Read(null0);
  rd.Read(unk2);
  rd.ReadString(albedoTexture);
  rd.Read(pulseFrequency);
  rd.Read(unk3);
  rd.Read(velocity);
  rd.Read(unk4);
  rd.Read(fogFactor);
  rd.Read(blended);
  rd.Read(fogOutFactor);
  rd.Read(vertexAlpha);
}

void BumpSpecular::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.Read(ambient);
  rd.Read(diffuse);
  rd.Read(specular);
  rd.Read(unk1);
  rd.Read(generatedShadows);
  rd.Read(translucent);
  rd.Read(masked);
  rd.Read(unk2);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(albedoUVOffset);
  rd.Read(normalUVOffset);
  rd.Read(blended);
}

void TexBlend::Read(BinReaderRef rd) {
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
  Material::Read(rd);
  rd.Read(ambient);
  rd.Read(diffuse);
  rd.Read(specular);
  rd.Read(unk1);
  rd.Read(vertexAlpha);
  rd.Read(unk2);
  rd.Read(unk3);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(albedoUVOffset);
  rd.Read(normalUVOffset);
  rd.Read(textureVelocity);
  rd.Read(depthBias);
  rd.Read(isBlended);
  rd.Read(data2);
}

void TintDistort::Read(BinReaderRef rd) {
  Material::Read(rd);
  rd.ReadString(alebedoTexture);
  rd.ReadString(normalTexture);
  rd.Read(albedoUVScale);
  rd.Read(normalUVScale);
  rd.Read(albedoUVOffset);
  rd.Read(normalUVOffset);
  rd.Read(textureVelocity);
  rd.Read(isBlended);
}

void Material::Write(BinWritterRef rd) const {
  rd.Write(unk);
  rd.WriteT(meshName);
  rd.WriteT(materialName);
  rd.WriteT(shaderType);
  rd.WriteT(shaderName);
  rd.Write(unk0);
}

void BumpAnisotropic::Write(BinWritterRef rd) const {
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
  rd.Write(masked);
  rd.Write(blended);
}

void Glow::Write(BinWritterRef rd) const {
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

void Unlit::Write(BinWritterRef rd) const {
  Material::Write(rd);
  rd.Write(ambient);
  rd.Write(diffuse);
  rd.Write(unk1);
  rd.Write(generatedShadows);
  rd.Write(translucent);
  rd.Write(null0);
  rd.Write(unk2);
  rd.WriteT(albedoTexture);
  rd.Write(pulseFrequency);
  rd.Write(unk3);
  rd.Write(velocity);
  rd.Write(unk4);
  rd.Write(fogFactor);
  rd.Write(blended);
  rd.Write(fogOutFactor);
  rd.Write(vertexAlpha);
}

void BumpSpecular::Write(BinWritterRef rd) const {
  Material::Write(rd);
  rd.Write(ambient);
  rd.Write(diffuse);
  rd.Write(specular);
  rd.Write(unk1);
  rd.Write(generatedShadows);
  rd.Write(translucent);
  rd.Write(masked);
  rd.Write(unk2);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(albedoUVOffset);
  rd.Write(normalUVOffset);
  rd.Write(blended);
}

void TexBlend::Write(BinWritterRef rd) const {
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
  Material::Write(rd);
  rd.Write(ambient);
  rd.Write(diffuse);
  rd.Write(specular);
  rd.Write(unk1);
  rd.Write(vertexAlpha);
  rd.Write(unk2);
  rd.Write(unk3);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(albedoUVOffset);
  rd.Write(normalUVOffset);
  rd.Write(textureVelocity);
  rd.Write(depthBias);
  rd.Write(isBlended);
  rd.Write(data2);
}

void TintDistort::Write(BinWritterRef rd) const {
  Material::Write(rd);
  rd.WriteT(alebedoTexture);
  rd.WriteT(normalTexture);
  rd.Write(albedoUVScale);
  rd.Write(normalUVScale);
  rd.Write(albedoUVOffset);
  rd.Write(normalUVOffset);
  rd.Write(textureVelocity);
  rd.Write(isBlended);
}

REFLECT(CLASS(Material), MEMBER(unk), MEMBER(meshName), MEMBER(materialName),
        MEMBER(shaderType), MEMBER(shaderName), MEMBER(unk0))

REFLECT(CLASS(BumpAnisotropic), MEMBER(alebedoTexture), MEMBER(normalTexture),
        MEMBER(anisotropyTexture), MEMBER(ambient), MEMBER(diffuse),
        MEMBER(specular), MEMBER(unk1), MEMBER(albedoUVScale),
        MEMBER(normalUVScale), MEMBER(masked), MEMBER(blended))

REFLECT(CLASS(Glow), MEMBER(glowTexture), MEMBER(glowUVScale),
        MEMBER(glowUVOffset), MEMBER(velocity), MEMBER(glowLevel),
        MEMBER(glowFactor), MEMBER(blended), MEMBER(fogFactor))

REFLECT(CLASS(Unlit), MEMBER(ambient), MEMBER(diffuse), MEMBER(unk1),
        MEMBER(generatedShadows), MEMBER(translucent), MEMBER(null0),
        MEMBER(unk2), MEMBER(albedoTexture), MEMBER(pulseFrequency),
        MEMBER(unk3), MEMBER(velocity), MEMBER(unk4), MEMBER(fogFactor),
        MEMBER(blended), MEMBER(fogOutFactor), MEMBER(vertexAlpha))

REFLECT(CLASS(BumpSpecular), MEMBER(ambient), MEMBER(diffuse), MEMBER(specular),
        MEMBER(unk1), MEMBER(generatedShadows), MEMBER(translucent),
        MEMBER(masked), MEMBER(unk2), MEMBER(alebedoTexture),
        MEMBER(normalTexture), MEMBER(albedoUVScale), MEMBER(normalUVScale),
        MEMBER(albedoUVOffset), MEMBER(normalUVOffset), MEMBER(blended))

REFLECT(CLASS(TexBlend), MEMBER(alebedo0Texture), MEMBER(alebedo1Texture),
        MEMBER(normalTexture), MEMBER(ambient), MEMBER(diffuse),
        MEMBER(specular), MEMBER(unk1), MEMBER(texture1Scale),
        MEMBER(texture2Scale), MEMBER(texture3Scale), MEMBER(unk2),
        MEMBER(applyNormalTo1stTextureOnly), MEMBER(unk3))

REFLECT(CLASS(Overlay), MEMBER(ambient), MEMBER(diffuse), MEMBER(specular),
        MEMBER(unk1), MEMBER(vertexAlpha), MEMBER(unk2), MEMBER(unk3),
        MEMBER(alebedoTexture), MEMBER(normalTexture), MEMBER(albedoUVScale),
        MEMBER(normalUVScale), MEMBER(albedoUVOffset), MEMBER(normalUVOffset),
        MEMBER(textureVelocity), MEMBER(depthBias), MEMBER(isBlended),
        MEMBER(data2))

REFLECT(CLASS(TintDistort), MEMBER(alebedoTexture), MEMBER(normalTexture),
        MEMBER(albedoUVScale), MEMBER(normalUVScale), MEMBER(albedoUVOffset),
        MEMBER(normalUVOffset), MEMBER(textureVelocity), MEMBER(isBlended))

ReflectedInstance GetReflectedMaterial(MaterialVariant &mtr) {
  return std::visit(
      [](auto &data) {
        using MType = std::decay_t<decltype(data)>;

        return ReflectedInstance(GetReflectedClass<MType>(), &data);
      },
      mtr);
}
