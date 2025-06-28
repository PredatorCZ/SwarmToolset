#pragma once
#include "aa_bounding_box.hpp"
#include "dx_types.hpp"

struct ResourceMaterial;
struct WorldObject;

struct Collider_unk {
  int SetupCapsule(const Vector &segmentP0, const Vector &segmentP1,
                   float radius, float a5, float a6, float a7);
  void _49AD80(const Vector &a0, const Vector &a1);

  Vector origin;
  Vector segmentP1;
  Vector rayDirection;
  float distance;
  float radius;
  float field_2C;
  float field_30;
  float field_34;
  AABoundingBox bbox;
  int collisionTypeFlags = 511;
  Vector field_68;
  Vector field_74;
  Vector field_80;
  float field_8C;
  ResourceMaterial *material;
};

struct Collider {
  Collider_unk field_4;
  int field_98;
  WorldObject *worldObject;
};
