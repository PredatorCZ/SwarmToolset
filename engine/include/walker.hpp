#pragma once
#include "aa_bounding_box.hpp"
#include "dx_types.hpp"
#include <list>
#include <vector>

struct AIEntity;
struct ResourceMaterial;

struct UnkStruct0 {
  void _470960(float radius);
  void _4709C0(Vector &a1, Matrix &a2, double a4, Matrix &a5,
               double a6);
  std::list<UnkStruct0>::iterator field_0;
  AIEntity *aiEntity;
  float field_8;
  Vector field_C;
  Vector field_18;
  int field_24;
  double field_28;
  double field_30;
  AABoundingBox bounds;
  int field_64;
};

struct UnkStruct1 {
  AIEntity *aiEntity;
  float navigatorCapsuleRadius;
  float navigatorCapsuleRadiusIgnore;
  Vector field_C;
  Vector field_18;
  int field_24;
  double field_28;
  double field_30;
  char field_38;
  AABoundingBox bounds;
};

struct Walker {
  ResourceMaterial *Material() { return material; }
  float GetNavigatorCapsuleRadius() { return field_E0.navigatorCapsuleRadius; }
  Vector &GetNavigatorCapsuleOffset() { return navigatorCapsuleOffset; }
  void SetActiveStatus(bool isActive) { this->isActive = isActive; }
  void SetMovingZigZag(bool moveZigZag) { movingZigZag = moveZigZag; }

  AIEntity *aiEntity;
  Vector navigatorCapsuleOffset;
  float navigatorBaseSizeX;
  float navigatorBaseSizeY;
  float navigatorBaseSizeZ;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  char field_2C;
  char field_2D;
  float field_30;
  float field_34;
  int allowFastRun;
  int movingZigZag;
  char avoidance;
  Matrix field_44;
  Matrix field_84;
  int field_C4;
  float field_C8;
  int field_CC;
  int field_D0;
  float field_D4;
  ResourceMaterial *material;
  bool isActive;
  UnkStruct1 field_E0;
  std::vector<void *> field_148;
  std::vector<void *> field_158;
  std::vector<void *> field_168;
  std::vector<bool> field_178;
  std::vector<Matrix> field_18C;
  int field_19C;
};
