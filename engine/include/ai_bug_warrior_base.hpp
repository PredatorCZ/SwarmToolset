#pragma once
#include "ai_bug_walker.hpp"
#include "ai_four_state_matrix.hpp"

struct ResourceObjectAnimationSet;
struct AIAnimation;
struct UnkStruct0;
struct SurfaceEffects;
struct SLVariableSetVector3;
struct IncomingDamage;

enum AISM {
  AISM_NONE,
  AISM_PLAYANIM,
  AISM_OUTOFGROUND,
  AISM_JUMP,
  AISM_BEENHIT,
  AISM_TANKERBUGL2,
  AISM_VEHICLELAND,
  AISM_VEHICLETAKEOFF,
  AISM_DROPSHIPFLYTOHOVER,
  AISM_DROPSHIPHOVER,
  AISM_DROPSHIPHOVERTOLAND,
  AISM_MANSTATICGUN,
};

struct AIBugWarriorBase : AIBugWalker, AIFourStateMatrix {
  virtual bool field_C4() = 0;
  virtual void field_C8(IncomingDamage &dmg, int unk) = 0;
  virtual double GetDefensePercentageChance() { return 0; }
  virtual ResourceObjectAnimationSet *GetAnimSetResource(int32_t index) = 0;
  virtual void field_D4() {}
  virtual bool IsInActiveState() = 0;
  virtual void field_DC() {}
  virtual bool field_E0() { return true; }
  virtual void CloneWarrior(AIBugWarriorBase *other);
  virtual uint32_t GetRootBoneIndex() = 0;
  virtual Vector field_EC() { return {4, 2, 4}; }
  virtual float GetHullSizeFactor() { return 1; }
  virtual float field_F4() { return 0.25; }
  virtual uint32_t field_F8(uint32_t) = 0;
  virtual int32_t field_FC() = 0;
  virtual float GetAttackStrength();
  virtual float GetAttackPredictionSpeed();
  virtual float GetIdleRangeMin();
  virtual float GetIdleRangeMax();
  virtual float GetIdleChance();
  virtual float GetIdleCone();
  virtual float GetAlertRangeMin();
  virtual float GetAlertRangeMax();
  virtual float GetAlertChance();
  virtual float GetAlertCone();
  virtual float GetDamageNonPlayerFactor() = 0;
  virtual float GetDeltaHealthForGib() { return 1.0; }
  virtual float GetBodyMovementFactor() { return 0.001; }
  virtual ResourcePtr<ResourceObjectModel> GetModelResource() = 0;
  virtual ResourcePtr<ResourceObjectModel> GetDeadModelResource() = 0;
  virtual ResourcePtr<ResourceObjectModel> GetBurntModelResource();
  virtual bool field_140() { return false; }

  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  void field_30() override;
  void field_34() override;
  void field_38() override;
  void ApplyDamage(IncomingDamage &dmg) override;
  void field_48(WorldObject &obj) override;
  void field_4C() override;
  bool IsAIType(AITYPEID typeId) override;
  void field_74() override;
  float GetSpottingBias(AIEntity *entity) override;
  void field_9C(int, int, float) override;
  void field_A0(AIAnimation *a2, int a3) override;

  void SetActiveStatus(bool isActive) override;
  void func_8() override;
  void Process() override;

  void _4E7180();
  void _4ED2E0();
  void SetStatePlayAnim();
  void _4E3670();
  void _4DFDF0();
  void SetStateIdleByAlertState();
  void SetStateMove();
  void _4EAB20();
  void _4E9C60();
  void SetStateRagdoll();
  void SetStateOutOfGround();
  void SetStateJump();
  void SetStateFlinch();
  AIAnimation *_4E8130(ResourceObjectAnimationSet *animSet, bool unk);
  void _4E8D90(const Vector &a2, bool moveZigZag, bool stickToWaypoints);
  void _4ED8E0(bool ignite, bool explode, float blastDamage);
  void TakeDamage(float amount);
  void TakeLimbDamage(float amount);
  void SetMovingZigZag(bool moveZigZag);
  bool DetachLimb(uint32_t boneIndex);
  void _4E0160();
  void _4E1AE0(WorldObjectModel *obj);
  Vector _4E2730(float arg4);
  void _4E28B0();
  float RemoveLimbHealth(uint32_t limbIndex, float amount);
  bool _4E3910(uint32_t limbIndex);
  void SetLimbHealth(uint32_t limbIndex, float health);
  void SetStateDieElectrify();
  void _4EEA70();

  int32_t field_818;
  int32_t field_81C;
  std::map<int32_t, float> limbsHealth;
  bool field_82C;
  AISM specialMode;
  float healthLegs;
  bool fightTrack;
  bool fightStrikeTrack;
  Vector hitVec;
  ResourceObjectAnimationSet *animType;
  AIAnimation *anim;
  float aiAnimTime[4];
  bool waypointsNarrow;
  bool movingZigZag;
  int32_t field_864;
  int32_t allowFastRun;
  UnkStruct0 *field_86C;
  UnkStruct0 *field_870;
  bool electrify;
  bool burntModelSwitch;
  int32_t cosmeticVulnerability;
  float ignoreRadius;
  bool ignoreUseDeltaY;
  float ignoreDeltaY;
  SurfaceEffects *surfaceEffects;
  ResourceObjectAnimationSet *overrideAnimSet;

  SLVariableSet *sl_quicksave;
  SLVariableTemplate<float> *sl_healthLegs;
  SLVariable *sl_fightStrike;
  SLVariable *sl_fightStrikeTrack;
  SLVariableSetVector3 *sl_hitVec;
  SLVariableAbstractRef *sl_animType;
  SLVariableTemplate<uint32_t> *sl_anim;
  SLVariableTemplate<float> *sl_aiAnimTime[4];
  SLVariable *moveWPTight;
  SLVariable *moveZigZag;
  int32_t field_8C4;
  SLVariable *sl_electrify;
  SLVariable *sl_burntModelSwitch;
  SLVariableTemplate<uint32_t> *sl_cosmeticVulnerability;
  SLVariableTemplate<float> *sl_ignoreRadius;
  SLVariable *sl_ignoreUseDeltaY;
  SLVariableTemplate<float> *sl_ignoreDeltaY;

  static int dword_D2EF4C;
  static int INFO_WARRIORBUGBASE_TOTAL;
  static int INFO_WARRIORBUGBASE;
};
