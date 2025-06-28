#include "core.hpp"

struct TextureVelocity : Vector2 {
  void ReflectorTag();
};

struct ResourceShaderBumpTexBlend2 : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture1;
  FilePath<FilePathType::Image> diffuseTexture2;
  FilePath<FilePathType::Image> normalMapTexture;
  Color ambient;
  Color diffuse;
  Color specular;
  float Texture1Scale;
  float Texture2Scale;
  float Texture3Scale;
  bool applyNormalTo1stTextureOnly;
};

struct ResourceShaderOverlay : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture;
  FilePath<FilePathType::Image> normalMapTexture;
  Color ambient;
  Color diffuse;
  Color specular;
  bool vertexAlpha;
  float diffuseUScale;
  float diffuseVScale;
  float normalUScale;
  float normalVScale;
  float diffuseUOffset;
  float diffuseVOffset;
  float normalUOffset;
  float normalVOffset;
  TextureVelocity textureVelocity;
  uint32 depthBias;
  bool blended;
};

struct ShaderParamsBumpSpec : ResourcePack {
  ResourceRef shader;
  bool getDefaults;
  Color ambient;
  Color diffuse;
  Color specular;
  float diffuseUScale;
  float diffuseVScale;
  float normalUScale;
  float normalVScale;
  float diffuseUOffset;
  float diffuseVOffset;
  float normalUOffset;
  float normalVOffset;
};

struct ResourceShaderAnisotropic : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture;
  FilePath<FilePathType::Image> normalMapTexture;
  FilePath<FilePathType::Image> anisotropicMapTexture;
  Color ambient;
  Color diffuse;
  Color specular;
  float diffuseUScale;
  float diffuseVScale;
  float normalUScale;
  float normalVScale;
  bool alphaTested;
  bool doubleFaced;
  bool ignoreMipmaps;
  bool blended;
};

struct ResourceShaderUnlit : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture;
  Color ambient;
  Color diffuse;
  bool alphaBlended;
  bool alphaTested;
  bool vertexAlpha;
  bool generateShadows;
  BLEND srcBlend;
  BLEND destBlend;
  float pulseFrequency;
  TextureVelocity textureVelocity;
  float fogFactor;
  float fogOutFactor;
  bool blended;
};

struct ResourceShaderPhong : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture;
  FilePath<FilePathType::Image> normalMapTexture;
  Color ambient;
  Color diffuse;
  Color specular;
  bool alphaBlended;
  bool alphaTested;
  bool generateShadows;
  float diffuseUScale;
  float diffuseVScale;
  float normalUScale;
  float normalVScale;
  float diffuseUOffset;
  float diffuseVOffset;
  float normalUOffset;
  float normalVOffset;
  bool doubleFaced;
  bool ignoreMipmaps;
  bool blended;
};

struct ResourceShaderGlow : ResourcePack {
  FilePath<FilePathType::Image> glowTexture;
  float glowUScale;
  float glowVScale;
  float emissiveFactor;
  float glowFactor;
  TextureVelocity textureVelocity;
  float fogFactor;
  bool blended;
};

struct ResourceShaderTintDistort : ResourcePack {
  FilePath<FilePathType::Image> tintTexture;
  FilePath<FilePathType::Image> distortTexture;
  Color ambient;
  TextureVelocity textureVelocity;
  bool blended;
};

struct ResourceShaderTexBlend3 : ResourcePack {
  FilePath<FilePathType::Image> diffuseTexture1;
  FilePath<FilePathType::Image> diffuseTexture2;
  FilePath<FilePathType::Image> diffuseTexture3;
  Color ambient;
  Color diffuse;
  Color specular;
  float texture1Scale;
  float texture2Scale;
  float texture3Scale;
};
