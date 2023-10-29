#pragma once
#include "core.hpp"

struct ResourceMaterialPhysicsProperties {
  float density;
  float friction;
  float bounce;
  void ReflectorTag();
};

struct ResourceMaterialDamageProperties {
  int32 heatFlammable;
  int32 blastFlammable;
  void ReflectorTag();
};

struct ResourceMaterialDamageEffect {
  uint32 valueParticle;
  ResourceArray particles;
  uint32 valueDecal;
  ResourceArray decals;
  uint32 valueSound;
  ResourceArray sounds;
  void ReflectorTag();
};

struct ResourceMaterialDamageEffects {
  ResourceMaterialDamageEffect pierceSoft;
  ResourceMaterialDamageEffect pierceHard;
  ResourceMaterialDamageEffect slash;
  ResourceMaterialDamageEffect punch;
  ResourceMaterialDamageEffect blast;
  ResourceMaterialDamageEffect heat;
  ResourceMaterialDamageEffect corrosive;
  ResourceMaterialDamageEffect electricity;
  ResourceMaterialDamageEffect psiOps;
  ResourceMaterialDamageEffect light;
  ResourceMaterialDamageEffect notSet;
  void ReflectorTag();
};

struct ResourceMaterialDamagingRates {
  int32 pierceSoft;
  int32 pierceHard;
  int32 slash;
  int32 punch;
  int32 blast;
  int32 heat;
  int32 corrosive;
  int32 electricity;
  int32 psiOps;
  int32 light;
  void ReflectorTag();
};

struct ResourceMaterial : ResourcePack {
  std::string materialName;
  CollisionFlags collisionFlags;
  ResourceMaterialPhysicsProperties physicsProperties;
  ResourceMaterialDamageProperties damageProperties;
  ResourceMaterialDamageEffects damageEffects;
  ResourceMaterialDamagingRates damagingRates;
  ResourceRef dustParticleResource;
  ResourceArray playerFootstepResource;
  ResourceArray humanFootstepResource;
  ResourceArray warriorBaseFootstepResource;
  ResourceRef dustRingParticleResouce;
};
