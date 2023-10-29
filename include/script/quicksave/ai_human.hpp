#pragma once
#include "script/core.hpp"
#include "script/enum_share.hpp"

struct AIHumanStartWeapons {
  AIWT startWeaponSlot1;
  AIWT startWeaponSlot2;
  AIWT startWeaponSlot3;
  bool MORITIA_MK4;
  bool MORITIA_MK2_SHOTGUN;
  bool MORITIA_MK2_GRENADE;
  bool HEAVY_SHOTGUN;
  bool MORITIA_MK2_ZOOM;
  bool MORITIA_MK2_CARBINE;
  bool ROCKET_LAUNCHER;
  bool RAILGUN;
  bool MISSILE_LAUNCHER;
  bool PSIOP_FAKE;
  void ReflectorTag();
};

struct AIHumanDeath {
  bool gibNotLaunch;
  float gibForce;
  void ReflectorTag();
};

struct AIHumanQuicksave {
  AIThreeStateMatrix aiThreeStateMatrix;
  ResourceRef pSwitchWeapon;
  Vector vLastAim;
  Matrix mWorldEndAnim;
  float dLastSpottingTime;
  float dNextAttractTime;
  bool bJustTurned;
  bool bTargetDied;
  float dLastPlayerLookTime;
  Vector vBonePos;
  bool bThrowingGrenade;
  float dLastGrenadeTime;
  float dLastFireTime;
  AIHSM humanSpecialMode;
  uint32 nSquadMemberID;
  float fPreviousGradient;
  float nPreviousSpeed;
  AIMODE ePrevMode;
  ResourceRef pLoopAnim;
  ResourceRef pLoopAnimSet;
  float dLoopAnimMaxTime;
  uint32 nLoopAnimReps;
  uint32 nLoopAnimMaxReps;
  float dLoopAnimTimeStart;
  STANDARD_POSE eLoopAnimStandardPose;
  uint32 nSquadPathSegment;
  uint32 nStuckTimer;
  ResourceRef pAttachMatrixObject;
  Vector vAttachOffset;
  uint32 nDropShipStage;
  uint32 nDropShipSide;
  bool bKneeling;
  float fKneelTimer;
  bool bAccuratePoints;
  float fAccuratePointHeading;
  uint32 nAccuratePointWait;
  ResourceRef pHotSpot;
  float fBlindTime;
  ResourceRef pBreakIgnoreTarget;
  bool bBreakIgnore;
  bool bGunState;
  float fPersonalGrenadeChance;
  float fPersonalAttractTurnChance;
  float fPersonalKneelChance;
  bool bBypassSeuquencerAdvance;
  bool bForceToSpot;
  ResourceRef pTurnToFaceObject;
  float fTurnToFaceAngle;
  ResourceArray pTurnToFaceActionList;
  float fBackupVulnerability;
  ResourceRef delayedSFX_Resource;
  uint32 delayedSFX_Rank;
  float delayedSFX_Time;
  uint32 nSaluteStage;
  float fSaluteAngle;
  float fSalutePrevAngle;
  bool bWasSentry;
  AIALERT eBackupAlertState;
  float dTemporaryIgnoreTime;
  uint32 nMaxSpeed;
  bool bShouldUsePelvisPos;
  void ReflectorTag();
};

struct AIPlayerQuicksave {
  float viewPitch;
  AIWEAPMODE weaponDesMode;
  float velFactor;
  Vector vel;
  Vector floorVel;
  bool bDropping;
  float duckVal;
  bool bDuckControl;
  ResourceRef pFloorObject;
  uint32 floorObjectBoneNum;
  Matrix floorObjectMatrix;
  ResourceRef pLadder;
  ResourceRef pHandGrenade;
  bool bDesHandGrenade;
  float shieldVal;
  float shieldDamageTime;
  ResourceRef pTorch;
  ResourceRef pDropPod;
  bool bDisableWeapon;
  bool bEvilEyeOn;
  void ReflectorTag();
};
