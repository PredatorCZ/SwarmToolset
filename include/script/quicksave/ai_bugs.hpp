#pragma once
#include "ai_base.hpp"

struct AIBugWarriorBaseQuicksave {
  AIFourStateMatrix aiFourStateMatrix;
  float healthLegs;
  bool bFightStrike;
  bool bFightStrikeTrack;
  Vector hitVec;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[4];
  bool bMoveWPTight;
  bool bMoveZigZag;
  bool bElectrify;
  bool bBurntModelSwitch;
  bool cosmeticVulnerability;
  bool IgnoreRadius;
  bool IgnoreUseDeltaY;
  bool IgnoreDeltaY;
  void ReflectorTag();
};

struct AIBugChariotQuicksave {
  AIThreeStateMatrix aiThreeStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  Vector millingCentre;
  void ReflectorTag();
};

struct AIBugFlyerBaseQuicksave {
  AIFlyerTwoStateMatrix aiFlyerTwoStateMatrix;
  bool turningInFlyerZone;
  bool forceFindPosition;
  float timeSinceLastScreech;
  Vector HitVec;
  Resource pAnim;
  float animTime[2];
  float desSpeed;
  bool bLaden;
  ResourceRef pFlyerZone;
  float flutterAnimTime;
  void ReflectorTag();
};

struct AIBugHopperQuicksave {
  uint32 fightPhase; //??
  bool flyOverTarget;
  Vector cacheAITargetPos;
  bool bStrikeReady;
  void ReflectorTag();
};

struct AIBugPlasmaQuicksave {
  AITwoStateMatrix aiTwoStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  bool bReqFireBolt;
  bool reqPreLaunchEffect;
  bool bBossModeVulnerable;
  float compoundDamage;
  bool bInitialised;
  float cowerTimeout;
  AIPBSM pbSpecialMode;
  uint32 cowerMode;
  ResourceRef pSpray;
  ResourceRef pNucBlastEffect1;
  ResourceRef pNucBlastEffect2;
  Vector sonicDir;
  void ReflectorTag();
};

enum class AIBugBabyPlasmaSpecialMode {
  NONE,
  OUTOFGROUND,
  MULTIWAYPOINT_NETWORK,
};

struct AIBugBabyPlasmaQuicksave {
  AIThreeStateMatrix aiThreeStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  bool bFightStrike;
  bool canIncreaseAccuracy;
  bool multiWPDeltaHealth;
  bool launchedFireball;
  AIBugBabyPlasmaSpecialMode psSpecialMode;
  float minMoveTime;
  float headElevation;
  uint32 currentVarianceIndex;
  ResourceRef pSpray;
  ResourceRef pNucBlastEffect1;
  ResourceRef pNucBlastEffect2;
  void ReflectorTag();
};

struct AIBugBlasterQuicksave {
  AITwoStateMatrix aiTwoStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  Vector projectileLaunchPos; //;
  bool reqLaunchProjectile;
  float nextStrikeTime;
  bool bFightStrike;
  bool launchToggle;
  bool canIncreaseAccuracy;
  bool bUprightMatrix;
  uint32 currentVarianceIndex;
  void ReflectorTag();
};

struct AIBugTankerBabyQuicksave {
  AIThreeStateMatrix aiThreeStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[3];
  Vector targetFirePos;
  ResourceRef pSpark;
  bool sparkStarted;
  std::string tbSpecialMode; // TODO figure out
  float minMoveTime;
  bool canIncreaseAccuracy;
  float multiWPDeltaHealth;
  ResourceRef pSpray;
  uint32 currentVarianceIndex;
  void ReflectorTag();
};

struct AIBugWarriorTigerSpitQuicksave {
  bool launchedFireBall;
  bool reqLaunchSpitLong;
  bool reqLaunchSpitShort;
  Vector spitLaunchPos;
  bool canIncreaseAccuracy;
  ResourceRef lastSightedTarget;
  uint32 currentVarianceIndex;
  void ReflectorTag();
};

struct AIBugWarriorRoyalXQuicksave {
  bool finale;
  float rearUpDamageHealth;
  bool bReqExposeBelly;
  bool bCanFireSpray;
  ResourceRef pSpray;
  uint32 royalAttackType;
  float requestRoarBlastDamageTime;
  ResourceRef pSonicEffect;
  void ReflectorTag();
};

struct AIBugHopperFireflyQuicksave {
  bool reqFireBall;
  float desFireTime;
  ResourceRef pSpray;
  bool bPlayingSprayAudio;
  float sprayEndTime;
  void ReflectorTag();
};

struct AIBugRhinoQuicksave {
  AIThreeStateMatrix aiThreeStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[3];
  bool bCharging;
  uint32 eRhinoAttackMode;
  Vector chargeToPos;
  bool bShakeHead;
  void ReflectorTag();
};

struct AIBugCliffMiteQuicksave {
  AITwoStateMatrix aiTwoStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  bool canFire;
  float missileDamageFactor;
  bool canIncreaseAccuracy;
  uint32 currentVarianceIndex;
  void ReflectorTag();
};

struct AIBugHopperRipplerQuicksave {
  bool targetAcquired;
  Vector kamikazeTargetPos;
  bool turningToTarget;
  void ReflectorTag();
};

struct AIBugWarriorRoyalQuicksave {
  uint32 royalAttackType;
  ResourceRef pSonicEffect;
  Vector vecToTarget;
  void ReflectorTag();
};

struct AIBugWarriorTigerShardQuicksave {
  bool reqLaunchShard;
  bool reqLaunchCone;
  Vector shardLaunchPos;
  bool canIncreaseAccuracy;
  ResourceRef lastSightedTarget;
  uint32 currentVarianceIndex;
  void ReflectorTag();
};

struct AIBugSentinelQuicksave {
  AITwoStateMatrix aiTwoStateMatrix;
  ResourceRef animType;
  uint32 pAnim;
  float aiAnimTime[2];
  uint32 fightStateFightState;
  uint32 fightStateLastFightState;
  bool bFlash;
  bool bRetracted;
  float lastFlashTime;
  bool bPlayedDyingAnim;
  void ReflectorTag();
};

struct AIBugTankerQuicksave {
  ResourceRef pSpray;
  ResourceRef pSpark;
  float stompTime;
  Vector stompPos;
  float stompStrength;
  float stompHotspot;
  float stompFalloff;
  float bBossRetract;
  float pAnim;
  float aiTime[2];
  void ReflectorTag();
};
