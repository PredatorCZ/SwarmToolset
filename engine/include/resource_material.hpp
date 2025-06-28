#pragma once
#include "resource_object.hpp"
#include <vector>

struct ResourceParticleDust;

struct ResourceMaterial : ResourceObject {
  struct DamageEffect {
    float valueParticle;
    float valueDecal;
    float valueSound;
    std::vector<void *> particles;
    std::vector<void *> decals;
    std::vector<void *> sounds;
  };

  std::string name;
  int collisionTypeFlags;
  float density;
  float friction;
  float bounce;
  float heatFlamable;
  float blastFlamable;
  DamageEffect damageEffect[11];
  std::string damageEffectName[11];
  int field_454;
  int field_458;
  int field_45C;
  int field_460;
  int field_464;
  int field_468;
  int field_46C;
  int field_470;
  int field_474;
  int field_478;
  int field_47C;
  ResourceParticleDust *dustParticleResource;
  std::vector<void *> playerFootstepResource;
  std::vector<void *> humanFootstepResource;
  std::vector<void *> warriorBaseFootstepResource;
  Abstract *dustRingParticleResource;
  std::set<void *> field_4B8;
};
