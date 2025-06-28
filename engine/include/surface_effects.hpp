#pragma once
#include "dx_types.hpp"
#include <list>

struct AIEntity;
struct ResourceMaterial;
struct ParticleSystemDust;
struct SurfaceEffectsTrigger;

struct SurfaceEffects {
  virtual ~SurfaceEffects();

  SurfaceEffects(AIEntity *ownerEntity);
  void SetDustRate(double rate);
  void _4965F0(int a2, float a3);
  void _4969E0(const Vector &unk);
  void _496D20(const Vector &arg0, const Vector &arg4, float a4);
  int field_4;
  AIEntity *entity;
  std::list<SurfaceEffectsTrigger *> triggers;
  ResourceMaterial *material;
  ParticleSystemDust *dustParticleSystem;
  Vector field_20;
  Vector field_2C;
  float field_38;
  int field_3C;
  double dustRate;
  Vector field_48;
  int field_54;
};
