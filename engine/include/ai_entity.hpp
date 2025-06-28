#pragma once
#include "ai_animation_blend_set.hpp"
#include "dx_types.hpp"
#include "model_detail_dynamic.hpp"
#include "sl_variable_template.hpp"
#include "watchable.hpp"
#include "watcher.hpp"
#include <vector>
#include "ai_types.hpp"

struct AIGroup;
struct AIWaypoint;
struct AIAction;
struct UnkStruct3;
struct AIAnimation;

struct AIEntity : ModelDetailDynamic, Watchable, Watcher {
  virtual void field_5C();
  virtual void field_60();
  virtual void field_64();
  virtual bool IsAIType(AITYPEID typeId) = 0;
  virtual void field_6C() {}
  virtual void field_70() {}
  virtual void field_74();
  virtual float GetSpottingBias(AIEntity *entity);
  virtual void field_7C() {}
  virtual void Clone(AIEntity *other);
  virtual void GetRotcketTargetInfo();
  virtual void AddHealth();
  virtual void SetPosition();
  virtual void YawRotation();
  virtual void field_94() {}
  virtual void field_98() {}
  virtual void field_9C(int, int, float) {}
  virtual void field_A0(AIAnimation *, int ) {}
  virtual void field_A4();
  virtual void field_A8() {}
  virtual void GetTorchSightModifier();
  virtual void field_B0() = 0;
  virtual void field_B4() = 0;
  virtual void field_B8() = 0;
  virtual void SetupAnimations() = 0;
  virtual void field_C0(int) {}

  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  void field_28() override;
  void field_2C() override;

  void SetActiveStatus(bool isActive) override;
  void field_10() override;

  Vector _455780(float unk, bool wideWaypoints);
  void _457A40(Vector *unk);
  void _4E28B0();
  bool _455C80(Matrix &a0Out, const Matrix &a1);
  AIEntity *GetAttacker();
  void RemoveFromWorldContext_0();
  void SetGroup(AIGroup *group, int *a3, int memberId);
  void ApplyNextVulnerability();
  void SetAlertState(int newState);
  void SetMovementMode(AIMODE newMode);
  void SetTarget(AIEntity *target, bool canSeeTarget);
  AIEntity *SpotEntity(float rangeMin, float rangeMax, int chance, int cone, bool a7);
  void SetAttacker(AIEntity *attacker);
  void SetHealth(float health);
  void RemoveHealth(float amount);

  int alertState;
  AIMODE movementMode;
  float vulnerability;
  char avoidance;
  char checkGradient;
  char forcedTarget;
  AIAnimationBlendSet animationBlendSet;
  char endOfWPChain;
  AIGroup *group;
  int field_420;
  int memberId;
  char isDummyEntity;
  char field_429;
  AIWaypoint *prevWaypoint;
  AIWaypoint *nextWaypoint;
  char stickToWaypoints;
  AIEntity *target;
  float health;
  float nextVulnerability;
  char nextVulnerabilityIsSet;
  char targettable;
  char addedInWorldContext;
  std::list<WorldObject>::iterator worldContextIter;
  std::vector<AIAction *> healthActions;
  AIEntity *attacker;
  Vector lastPos;
  Vector velocity;
  char field_478;
  Vector needToAdvanceWPPos;
  char canSeeTarget;
  Vector lastTargetPosition;
  UnkStruct3 *healthbar;
  SLVariableSet *quicksave;
  SLVariableAbstractRef *m_pRagDoll;
  SLVariableTemplate<uint32_t> *m_bEndOfWPChain;
  SLVariableTemplate<uint32_t> *m_fNextVulnerability;
  SLVariableTemplate<uint32_t> *m_bNextVulnerabilityIsSet;
  SLVariableAbstractRef *m_pAggressor;
  SLVariableSet *m_LastPos;
  SLVariableSet *m_Velocity;
  SLVariableTemplate<uint32_t> *m_bNeedToAdvanceWP;
  SLVariableSet *m_bNeedToAdvanceWPPos;
  SLVariableTemplate<uint32_t> *m_bCanSeeTarget;
  SLVariableSet *m_LastTargetPosition;
  SLVariableTemplate<uint32_t> *HasHealthBar;
};
