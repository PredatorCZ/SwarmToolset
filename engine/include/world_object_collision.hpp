#pragma once
#include "world_object.hpp"

struct Collidable;

struct WorldObjectCollision : WorldObject {
  void _91DC20(int a2);
  uint32_t GetBoneIndex() const { return boneIndex; }
  uint32_t _91DDB0();
  void _91E6B0(int a1, int collidableType, float a4);
  void _91E1B0();

  Collidable *collidable[4];
  float autoRangeFactors[3];
  float field_20;
  char field_24;
  int field_28;
  int field_2C;
  int field_30;
  uint32_t boneIndex;
  int field_38;
};
