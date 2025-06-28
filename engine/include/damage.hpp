#pragma once
#include "dx_types.hpp"

struct AIEntity;

struct IncomingDamage
{
  IncomingDamage() = default;
  IncomingDamage(const Vector &arg0, const Vector &arg1, const Vector &arg2, AIEntity *entity, float arg4);
  float bulletSoft;
  float bulletHard;
  float slash;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiops;
  float flash;
  float sonic;
  Vector field_2C;
  Vector field_38;
  Vector field_44;
  Vector field_50;
  float field_5C;
  AIEntity *entity;
};
