#pragma once
#include "dx_types.hpp"
#include "game_object.hpp"
#include "sl_variable_list_template.hpp"
#include "sl_variable_template.hpp"
#include <vector>

struct ModelDetailDynamic;
struct IncomingDamage;
struct SLVariableSetVector3;
struct SLVariableSetMatrix;

struct SLRagDollBone : GameObject {
  Vector sizeMin;
  Vector sizeMax;
  Vector center;
  float mass;
  int totalMass;
  float radius;
  Matrix matG;
  Vector posG;
  int index;
  int field_C8;
  float field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  int field_100;
  int field_104;
  int field_108;
  int field_10C;
  int field_110;
  int field_114;
  int field_118;
  int field_11C;
  int field_120;
  int field_124;
  int field_128;
  int field_12C;
  int field_130;
  int field_134;
  int field_138;
  int field_13C;
  int field_140;
  int field_144;
  int field_148;
  int field_14C;
  int field_150;
  int field_154;
  int field_158;
  int field_15C;
  int field_160;
  int field_164;
  int field_168;
  int field_16C;
  int field_170;
  int field_174;
  int field_178;
  int field_17C;
  int field_180;
  int field_184;
  Vector vertVel[8];
  Vector vertLocal[8];
  int field_248;
  int field_24C;
  int field_250;
  int field_254;
  int field_258;
  int field_25C;
  int field_260;
  int field_264;
  int field_268;
  int field_26C;
  int field_270;
  int field_274;
  int field_278;
  int field_27C;
  int field_280;
  int field_284;
  int field_288;
  char frozen;
  int field_290;
  int field_294;
  int field_298;
  SLVariableSetVector3 *sl_sizeMin;
  SLVariableSetVector3 *sl_sizeMax;
  SLVariableSetVector3 *centerL;
  SLVariableTemplate<float> *sl_mass;
  SLVariableTemplate<float> *sl_totalMass;
  SLVariableTemplate<float> *sl_radius;
  SLVariableSetMatrix *sl_matG;
  SLVariableSetVector3 *sl_posG;
  SLVariableTemplate<uint32_t> *boneRef;
  SLVariableSetVector3 *sl_vertVel[8];
  SLVariableSetVector3 *sl_vertLocal[8];
  SLVariable *sl_frozen;
};

struct RagDoll : GameObject {
  using Bones = std::list<SLRagDollBone>;
  void ApplyDamage(IncomingDamage &dmg);
  void AddBone(uint32_t boneIndex);
  void _661F80(float unk);
  bool _661D50(uint32_t limbIndex);
  void _6666B0(Bones &bones);
  void _661FB0(Bones &bones, float unk);
  void _663EB0(float unk);

  ModelDetailDynamic *model;
  float mass;
  std::vector<void *> bones;
  float timeActive;
  bool fullRagdoll;
  bool deletable;
  bool active;
  char field_67;

  SLVariableAbstractRef *sl_parentObject;
  SLVariableTemplate<float> *sl_mass;
  SLVariableListTemplate<SLVariableAbstractRef> *sl_bones;
  SLVariableTemplate<float> *sl_timeActive;
  SLVariable *sl_fullRgdoll;
  SLVariable *sl_deletable;
  SLVariable *sl_active;
};
