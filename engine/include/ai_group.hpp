#pragma once
#include "ai_types.hpp"
#include "world_object.hpp"

struct AIEntity;

struct AIGroup : WorldObject {
  void RemoveEntity(AIEntity *ent);
  void SetActive(bool isActive);
  void _47D0C0(bool unk);

  std::list<AIEntity *> entities;
  int alertState;
  AIMODE mode;
  int field_AC;
  int field_B0;
  int field_B4;
  int field_B8;
  int field_BC;
  int field_C0;
  int field_C4;
  int field_C8;
  int field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  int field_E8;
  char field_EC;
  char field_ED;
  char field_EE;
};
