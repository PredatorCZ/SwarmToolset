#pragma once
#include "damage.hpp"
#include "processable.hpp"
#include "world_object_model.hpp"

struct RagDoll;
struct ResourceObject;

struct ModelDetailDynamic : WorldObjectModel, Processable {
  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  void field_30() override;
  void field_38() override;
  void ApplyDamage(IncomingDamage &dmg) override;

  void Ignite(int a2, float a3, float a4);

  RagDoll *pRagDoll;
  bool beingControlled;
  bool hasBeenControlled;
  bool movable;
  float breakoutForce;
  float density;
  bool flamable;
  ResourceObject *pFlames;
  ResourceObject *pSmoke;
  int32_t flameListNum;
  int32_t smokeListNum;
  bool explosive;
  SLVariableSet *quicksave;
  SLVariableAbstractRef *m_pRagDoll;
  SLVariable *m_pFlames;
  SLVariable *m_pSmoke;
  SLVariable *m_FlameListNum;
  SLVariable *m_SmokeListNum;
};
