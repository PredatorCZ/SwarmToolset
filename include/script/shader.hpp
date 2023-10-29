#include "core.hpp"

struct ResourceShaderBumpTexBlend2 : ResourcePack {
  AFileInfo diffuseTexture1;
  AFileInfo diffuseTexture2;
  AFileInfo normalMapTexture;
  Color ambient;
  Color diffuse;
  Color specular;
  float Texture1Scale;
  float Texture2Scale;
  float Texture3Scale;
  bool applyNormalTo1stTextureOnly;
};

struct ResourceShaderOverlay : ResourcePack {
  AFileInfo diffuseTexture;
  AFileInfo normalMapTexture;
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
  Vector2 textureVelocity;
  bool depthBias;
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
  AFileInfo diffuseTexture;
  AFileInfo normalMapTexture;
  AFileInfo anisotropicMapTexture;
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
  AFileInfo diffuseTexture;
  Color ambient;
  Color diffuse;
  bool alphaBlended;
  bool alphaTested;
  bool vertexAlpha;
  bool generateShadows;
  BLEND srcBlend;
  BLEND destBlend;
  float pulseFrequency;
  Vector2 textureVelocity;
  float fogFactor;
  float fogOutFactor;
  bool blended;
};

struct ResourceShaderPhong : ResourcePack {
  AFileInfo diffuseTexture;
  AFileInfo normalMapTexture;
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
  AFileInfo glowTexture;
  float glowUScale;
  float glowVScale;
  float emissiveFactor;
  float glowFactor;
  Vector2 textureVelocity;
  float fogFactor;
  bool blended;
};

struct ResourceShaderTintDistort : ResourcePack {
  AFileInfo tintTexture;
  AFileInfo distortTexture;
  Color ambient;
  Vector2 textureVelocity;
  bool blended;
};

struct ResourceShaderTexBlend3 : ResourcePack {
  AFileInfo diffuseTexture1;
  AFileInfo diffuseTexture2;
  AFileInfo diffuseTexture3;
  Color ambient;
  Color diffuse;
  Color specular;
  float texture1Scale;
  float texture2Scale;
  float texture3Scale;
};
