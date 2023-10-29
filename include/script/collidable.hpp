#pragma once
#include "core.hpp"

enum COLLIDABLE {
  COLLIDABLE_NONE = -1,
  COLLIDABLE_BOUNDINGBOX,
  COLLIDABLE_BONEBOXES,
  COLLIDABLE_POLYGON,
};

struct ResourceObjectCollidableInfoTypes {
  COLLIDABLE collidable0Near;
  COLLIDABLE collidable1;
  COLLIDABLE collidable2;
  COLLIDABLE collidable3Far;
  void ReflectorTag();
};

struct ResourceObjectCollidableInfoRanges {
  float range01;
  float range12;
  float range23;
  void ReflectorTag();
};

struct ResourceObjectCollidableInfo : ResourcePack {
  ResourceObjectCollidableInfoTypes collidableTypes;
  float autoRanges;
  ResourceObjectCollidableInfoRanges collidableRanges;
};
