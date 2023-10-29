#pragma once
#include "core.hpp"

enum TDSTYPE {
  TDSTYPE_GLOBALEASY,
  TDSTYPE_GLOBALNORMAL,
  TDSTYPE_GLOBALHARD,
  TDSTYPE_GLOBALVHARD,
  TDSTYPE_LEVEL,
  TDSTYPE_NUM,
};

struct TuningDataScript : ResourcePack {
  TDSTYPE tdsType;
};

struct TuningDataScriptShake {
  float time;
  float angleX;
  float angleY;
  float angleZ;
  void ReflectorTag();
};

struct TuningDataScriptJolt {
  float time;
  float angleX;
  void ReflectorTag();
};

struct TuningDataScript_AIManagerGeneral {
  float maxDeadBodies;
  float warriorRumbleVolumeFactor;
  float warriorRumbleMaxDist;
  float warriorRumbleCutoffDist;
  void ReflectorTag();
};

struct TuningDataScript_AIManagerDeadBodyRemoval {
  float rangeFactor;
  float angleFactor;
  float ageFactor;
  float onFireFactor;
  float bodyFadeOutTime;
  float bigBodyBodyFadeOutTime;
  float maxNumberRagdolls;
  void ReflectorTag();
};

struct TuningDataScript_AIManager : TuningDataScript {
  TuningDataScript_AIManagerGeneral general;
  TuningDataScript_AIManagerDeadBodyRemoval deadBodyRemoval;
};

struct TuningDataScript_AmmoPickupAmmoBox {
  float checkRadius;
  float checkTime;
  float pickupNumber;
  float timePerPickup;
  void ReflectorTag();
};

struct TuningDataScript_AmmoPickupAmmoBundle {
  float checkRadius;
  float checkTime;
  void ReflectorTag();
};

struct TuningDataScript_AmmoPickup : TuningDataScript {
  TuningDataScript_AmmoPickupAmmoBox ammoBox;
  TuningDataScript_AmmoPickupAmmoBundle ammoBundle;
};

struct TuningDataScriptSpottingTargetBias {
  float player;
  float aiHuman;
  float vehicle;
  void ReflectorTag();
};

struct TuningDataScriptSpotting {
  float rangeMax;
  float rangeMin;
  float chance;
  float cone;
  void ReflectorTag();
};

struct TuningDataScriptSpotting3 {
  float rangeMax;
  float rangeMin;
  float rangeChance;
  float cone;
  void ReflectorTag();
};

struct TuningDataScriptSpotting2 : TuningDataScriptSpotting {
  float torchSightModifier;
  void ReflectorTag();
};

struct TuningDataScriptDamage {
  float pierceSoft;
  float pierceHard;
  float slash;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiOps;
  void ReflectorTag();
};

struct TuningDataScriptStrength
{
  float bulletSoft;
  float bulletHard;
  float slash;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiOps;
  void ReflectorTag();
};

struct TuningDataScriptPlayerStrength : TuningDataScriptStrength {
  float light;
  float sonic;
  void ReflectorTag();
};

struct TuningDataScriptPlayerShield : TuningDataScriptPlayerStrength {
  float rechargeDelay;
  float rechargeRate;
  void ReflectorTag();
};

struct TuningDataScriptCoreDamage : TuningDataScriptDamage {
  float coreRadius;
  float light;
  float sonic;
  void ReflectorTag();
};

struct TuningDataScriptDamage2 {
  float nonPlayerFactor;
  void ReflectorTag();
};

struct TuningDataScriptAttackForceBarge {
  float punch;
  void ReflectorTag();
};

struct TuningDataScript2FootImpact {
  float punchMultiplierFLeg;
  float punchMultiplierRLeg;
  float dustRateModifier;
  void ReflectorTag();
};

struct TuningDataScript3FootImpact : TuningDataScript2FootImpact {
  float punchMultiplierMLeg;
  void ReflectorTag();
};

struct TuningDataScriptNavigator {
  float capsuleRadius;
  float capsuleOffsetX;
  float capsuleOffsetY;
  float capsuleOffsetZ;
  float capsuleRadiusIgnore;
  float baseSizeX;
  float baseSizeY;
  float baseSizeZ;
  float maxGradient;
  void ReflectorTag();
};

struct TuningDataScriptNavigatorSpeed {
  float stepLength;
  float stepTime;
  float maxTurn;
  void ReflectorTag();
};

struct TuningDataScriptNetworkStrategy {
  float minTimeBeforeMove;
  float moveWaypointChance;
  float wpDeltaHealth;
  float deltaHealthMoveChance;
  void ReflectorTag();
};

struct TuningDataScriptBolt {
  float minDistance;
  float speed;
  float blastForce;
  float hotSpot;
  float fallOff;
  void ReflectorTag();
};

struct TuningDataScriptAccuracy {
  float minVariance;
  float maxVariance;
  float numberOfIntervals;
  float firePredictionTime;
  void ReflectorTag();
};

struct TuningDataScript_BabyPlasmaDamage : TuningDataScriptDamage2 {
  float thresholdForDamageToBody;
  void ReflectorTag();
};

struct TuningDataScript_BabyPlasma : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptDamage damageStrengthHead;
  TuningDataScriptDamage damageStrengthArse;
  TuningDataScript_BabyPlasmaDamage damage;
  TuningDataScriptAttackForceBarge attackForceBarge;
  TuningDataScript3FootImpact footImpact;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNetworkStrategy networkStrategy;
  TuningDataScriptBolt bolt;
  TuningDataScriptAccuracy accuracy;
};

struct TuningDataScriptFire {
  float resistanceThreshold;
  void ReflectorTag();
};

struct TuningDataScriptFire2 : TuningDataScriptFire {
  float onFireDamageRate;
  void ReflectorTag();
};

struct TuningDataScript_BlasterStrategy {
  float closeOnTargetChance;
  float attackRadius;
  void ReflectorTag();
};
struct TuningDataScript_BlasterAttack {
  float meleeAttackDist;
  float maxFiringRange;
  float horizontalFiringAngle;
  float verticalFiringAngle;
  void ReflectorTag();
};
struct TuningDataScript_BlasterAccuracy {
  float miniumumVariance;
  float maxiumumVariance;
  float numberOfIntervals;
  void ReflectorTag();
};
struct TuningDataScript_BlasterNavigator {
  float capsuleRadius;
  float capsuleOffsetX;
  float capsuleOffsetY;
  float capsuleOffsetZ;
  float capsuleRadiusIgnore;
  float baseSizeX;
  float baseSizeY;
  float baseSizeZ;
  float maxGradient;
  float gridLengthMin;
  float gridLengthMax;
  float gridWidth;
  float desiredResolutionX;
  float desiredResolutionZ;
  float jumpHeightMin;
  float jumpHeightMax;
  float desiredJumpResolution;
  float extraJumpHeightMax;
  float extraDesiredJumpResolution;
  void ReflectorTag();
};
struct TuningDataScript_BlasterProjectile {
  float fireRate;
  float force;
  float hotspot;
  float falloff;
  void ReflectorTag();
};
struct TuningDataScript_BlasterMisc {
  float facingAngle;
  void ReflectorTag();
};

struct TuningDataScript_Blaster : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptDamage damageStrength;
  TuningDataScriptDamage2 damage;
  TuningDataScriptAttackForceBarge attackForceBarge;
  TuningDataScriptFire fire;
  TuningDataScript_BlasterStrategy strategy;
  TuningDataScript_BlasterAttack attack;
  TuningDataScript_BlasterAccuracy accuracy;
  TuningDataScript_BlasterNavigator navigator;
  TuningDataScript_BlasterProjectile projectile;
  TuningDataScript_BlasterMisc misc;
};

struct TuningDataScript_ChariotStrategy {
  float scurryDistance;
  float millingMoveChance;
  float millingRadius;
  void ReflectorTag();
};

struct TuningDataScript_Chariot : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptDamage damageStrengthHead;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
  TuningDataScript_ChariotStrategy strategy;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
};

struct TuningDataScript_CliffMiteSpotting {
  float idleRangeMin;
  float idleRangeMax;
  float idleChance;
  float idleCone;
  float alertRangeMin;
  float alertRangeMax;
  float alertChance;
  float alertCone;
  float torchSightModifier;
  void ReflectorTag();
};
struct TuningDataScript_CliffMiteAttack {
  float maxFiringArc;
  float nearRange;
  float farRange;
  float nearChance;
  float farChance;
  void ReflectorTag();
};
struct TuningDataScript_CliffMiteMissile {
  float speed;
  float life;
  float damage;
  float minDamageFactor;
  void ReflectorTag();
};

struct TuningDataScript_CliffMiteAccuracy : TuningDataScriptAccuracy {
  void ReflectorTag();
};

struct TuningDataScript_CliffMite : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage damageStrength;
  TuningDataScript_CliffMiteSpotting spotting;
  TuningDataScript_CliffMiteAttack attack;
  TuningDataScript_CliffMiteMissile missile;
  TuningDataScriptDamage2 damage;
  TuningDataScript_CliffMiteAccuracy accuracy;
};

struct TuningDataScript_ElectricFenceFenceParameters {
  float electricityForce;
  float heightBottom;
  float heightTop;
  float testDelay;
  void ReflectorTag();
};

struct TuningDataScript_ElectricFence : TuningDataScript {
  TuningDataScriptDamage postDamageStrength;
  TuningDataScript_ElectricFenceFenceParameters fenceParameters;
};

struct TuningDataScriptFlyingVehicles {
  float flightSpeedSlow;
  float flightSpeedMedium;
  float flightSpeedFast;
  float rotationRate;
  void ReflectorTag();
};
struct TuningDataScript_FlyingVehiclesMarauderDropship : TuningDataScriptFlyingVehicles {
  float playerPosX;
  float playerPosY;
  float playerPosZ;
  float playerHeading;
  float playerHeadingArc;
  float playerPitch;
  float playerPitchArc;
  void ReflectorTag();
};

struct TuningDataScript_FlyingVehiclesBomberBomb {
  float napalmLaunchNum;
  float naplamLaunchTime;
  float naplamLaunchSize;
  float naplamBlastForce;
  float naplamBlastHotspot;
  float naplamBlastFalloff;
  float blastForce;
  float blastHotspot;
  float blastFalloff;
  float projectileLaunchSpeed;
  void ReflectorTag();
};
struct TuningDataScript_FlyingVehiclesDownDraft {
  float blastValue;
  float deltaTime;
  float rayLength;
  void ReflectorTag();
};

struct TuningDataScript_FlyingVehicles : TuningDataScript {
  TuningDataScriptFlyingVehicles gruntDropship;
  TuningDataScript_FlyingVehiclesMarauderDropship marauderDropship;
  TuningDataScriptFlyingVehicles cargoDropship;
  TuningDataScriptFlyingVehicles bomber;
  TuningDataScript_FlyingVehiclesBomberBomb bomberBomb;
  TuningDataScript_FlyingVehiclesDownDraft downDraft;
};

struct TuningDataScript_HandGrenadeFirstPerson {
  float countdownTime;
  float stayPrimedTime;
  float launchVelUp;
  float launchVelFore;
  void ReflectorTag();
};
struct TuningDataScript_HandGrenadeMovementData {
  float radius;
  float bounceNormalLoss;
  float bounceParallelVel;
  float rollingDrag;
  float activeTime;
  float trooperCheckDelay;
  void ReflectorTag();
};
struct TuningDataScript_HandGrenadeBlast {
  float force;
  float hotSpot;
  float fallOff;
  void ReflectorTag();
};
struct TuningDataScript_HandGrenadeSafeRadius {
  float player;
  float aIHuman;
  void ReflectorTag();
};

struct TuningDataScript_HandGrenade : TuningDataScript {
  TuningDataScript_HandGrenadeFirstPerson firstPerson;
  TuningDataScript_HandGrenadeMovementData movementData;
  TuningDataScript_HandGrenadeBlast blast;
  TuningDataScript_HandGrenadeSafeRadius safeRadius;
};

struct TuningDataScript_HopperStrength {
  float bulletHead;
  float bulletBody;
  float bulletWings;
  float bulletBlast;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperFlightSpeed {
  float slow;
  float medium;
  float fast;
  float vFast;
  float vvFast;
  void ReflectorTag();
};
struct TuningDataScript_HopperSpotting {
  float rangeMin;
  float rangeMax;
  float cone;
  float chance;
  float torchSightModifier;
  void ReflectorTag();
};
struct TuningDataScript_HopperAttack {
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_HopperAttackForce {
  float innerRadius;
  float outerRadius;
  float blast;
  float corrosive;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperAudio {
  float screechChance;
  float screechGibChance;
  void ReflectorTag();
};

struct TuningDataScript_Hopper : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
  TuningDataScript_HopperStrength strength;
  TuningDataScript_HopperFlightSpeed flightSpeed;
  TuningDataScript_HopperSpotting spotting;
  TuningDataScript_HopperAttack attack;
  TuningDataScript_HopperAttackForce attackForce;
  TuningDataScript_HopperAudio audio;
};

struct TuningDataScript_HopperFireflyStrength {
  float bulletHead;
  float bulletBody;
  float bulletWings;
  float blast;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflyFlightSpeed {
  float slow;
  float medium;
  float fast;
  float vFast;
  float vvFast;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflySpotting {
  float rangeMin;
  float rangeMax;
  float cone;
  float chance;
  float torchSightModifier;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflyAttack {
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflyAttackForce {
  float innerRadius;
  float outerRadius;
  float blast;
  float corrosive;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflyBolt {
  float blastForce;
  float blastHotspot;
  float falloff;
  float speed;
  void ReflectorTag();
};
struct TuningDataScript_HopperFireflyAudio {
  float screechChance;
  float screechGibChance;
  void ReflectorTag();
};

struct TuningDataScript_HopperFirefly : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
  TuningDataScript_HopperFireflyStrength strength;
  TuningDataScript_HopperFireflyFlightSpeed flightSpeed;
  TuningDataScript_HopperFireflySpotting spotting;
  TuningDataScript_HopperFireflyAttack attack;
  TuningDataScript_HopperFireflyAttackForce attackForce;
  TuningDataScript_HopperFireflyBolt bolt;
  TuningDataScript_HopperFireflyAudio audio;
};

struct TuningDataScript_HopperRipplerStrength {
  float bulletHead;
  float bulletBody;
  float bulletWings;
  float blast;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperRipplerFlightSpeed {
  float slow;
  float medium;
  float fast;
  float vFast;
  float vvFast;
  void ReflectorTag();
};
struct TuningDataScript_HopperRipplerSpotting {
  float rangeMin;
  float rangeMax;
  float cone;
  float chance;
  float torchSightModifier;
  void ReflectorTag();
};
struct TuningDataScript_HopperRipplerAttack {
  float strength;
  float speed;
  void ReflectorTag();
};
struct TuningDataScript_HopperRipplerAttackForce {
  float innerRadius;
  float outerRadius;
  float blast;
  float corrosive;
  float heat;
  void ReflectorTag();
};
struct TuningDataScript_HopperRipplerAudio {
  float screechChance;
  float screechGibChance;
  void ReflectorTag();
};

struct TuningDataScript_HopperRippler : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
  TuningDataScript_HopperRipplerStrength strength;
  TuningDataScript_HopperRipplerFlightSpeed flightSpeed;
  TuningDataScript_HopperRipplerSpotting spotting;
  TuningDataScript_HopperRipplerAttack attack;
  TuningDataScript_HopperRipplerAttackForce attackForce;
  TuningDataScript_HopperRipplerAudio audio;
};

struct TuningDataScript_HumanSpotting {
  float minimumInterval;
  float movingMultiplier;
  void ReflectorTag();
};
struct TuningDataScript_HumanSpottingAlert {
  float rangeMin;
  float rangeMax;
  float chance;
  float cone;
  float targetTimeout;
  void ReflectorTag();
};
struct TuningDataScript_HumanGrenade {
  float minimumInterval;
  float chance;
  float rangeMin;
  float rangeMax;
  float launchVel;
  float throwDelay;
  float maxAngle;
  float maxRandomOffset;
  void ReflectorTag();
};
struct TuningDataScript_HumanPsiOps {
  float maxKillDistance;
  float averageKillTime;
  float killGibForce;
  void ReflectorTag();
};
struct TuningDataScript_HumanAttract {
  float lookPlayerMinimumInterval;
  float lookPlayerMaximumInterval;
  float lookPlayerPersonalInterval;
  float lookPlayerChance;
  float noticePlayerDistance;
  float celebrateChance;
  float fireAttractMinimumInterval;
  float fireAttractMaximumInterval;
  float saluteRadius;
  void ReflectorTag();
};
struct TuningDataScript_HumanSize {
  float sizeX;
  float sizeY;
  float sizeZ;
  void ReflectorTag();
};
struct TuningDataScript_HumanNavigation {
  float capsuleRadius;
  float maxGradient;
  float baseSizeX;
  float baseSizeY;
  float baseSizeZ;
  float minStaticTurnAng;
  void ReflectorTag();
};
struct TuningDataScript_HumanDamageStrength {
  float strengthBlast;
  float strengthPierceSoft;
  float strengthPierceHard;
  float strengthSlash;
  float strengthPunch;
  float strengthHeat;
  float strengthCorrosive;
  float strengthElectric;
  float strengthLight;
  float strengthSonic;
  void ReflectorTag();
};
struct TuningDataScript_HumanBlastLaunch {
  float minVal;
  float multiplier;
  float timeStep;
  float maxSteps;
  void ReflectorTag();
};
struct TuningDataScript_HumanPunchLaunch {
  float minVal;
  void ReflectorTag();
};
struct TuningDataScript_HumanSetOnFire {
  float minVal;
  void ReflectorTag();
};
struct TuningDataScript_HumanGrenadesDropped {
  float minAmount;
  float maxAmount;
  float yVelocity;
  float xzVelocity;
  void ReflectorTag();
};
struct TuningDataScript_HumanKneeling {
  float kneelChance;
  float standChance;
  float minTime;
  void ReflectorTag();
};
struct TuningDataScript_HumanAttractTurn {
  float chance;
  float minAngle;
  float maxAngle;
  void ReflectorTag();
};
struct TuningDataScript_HumanSpeechChance {
  float killWarrior;
  float killTiger;
  float killBig;
  float killBlasterCliffmite;
  float killSentinelChariot;
  float killHopper;
  float throwGrenade;
  float wounded;
  float dying;
  float hopperDuck;
  float openFire;
  float ceaseFire;
  float ceaseFireDelay;
  float manDown;
  float manDownRadius;
  float dropShipDisembard;
  float friendlyFire;
  float fFMinInterval;
  float combatCrazy;
  float cCMaxHealth;
  float commentRange;
  float idleComment;
  float lowHealthMinInterval;
  float lowHealthMaxInterval;
  float lowHealthPersonalInterval;
  float minTimeSinceAttack;
  float minTimeSinceHurt;
  float lowHealth;
  float lowHealthHealth;
  float manDownMinInterval;
  float manDownMaxInterval;
  float manDownPersonalInterval;
  float greatShotRadius;
  float greatShotMinInterval;
  float greatShotPersonalInterval;
  float thankPlayerRadius;
  float thankPlayerMaxHealth;
  float thankPlayerMinInterval;
  float thankPlayerPersonalInterval;
  float blindedMinInterval;
  float blindedPersonalInterval;
  void ReflectorTag();
};
struct TuningDataScript_HumanTargetBias {
  float warrior;
  float tiger;
  float tigerShard;
  float tigerSpit;
  float royal;
  float royalX;
  float rhino;
  float babyTanker;
  float babyPlasma;
  float blaster;
  float chariot;
  float hopper;
  float fireFly;
  float rippler;
  float tanker;
  float plasma;
  float cliffMite;
  float sentinel;
  void ReflectorTag();
};
struct TuningDataScript_HumanSquad {
  float speed;
  float waitDistance;
  float distanceCheckInterval;
  float followMaxDist;
  float dropShipIgnoreTime;
  void ReflectorTag();
};

struct TuningDataScript_Human : TuningDataScript {
  TuningDataScriptSpotting spottingIdle;
  TuningDataScript_HumanSpotting spotting;
  TuningDataScript_HumanSpottingAlert spottingAlert;
  TuningDataScript_HumanGrenade grenade;
  TuningDataScript_HumanPsiOps psiOps;
  TuningDataScript_HumanAttract attract;
  TuningDataScript_HumanSize size;
  TuningDataScript_HumanNavigation navigation;
  TuningDataScript_HumanDamageStrength damageStrength;
  TuningDataScript_HumanBlastLaunch blastLaunch;
  TuningDataScript_HumanPunchLaunch punchLaunch;
  TuningDataScript_HumanSetOnFire setOnFire;
  TuningDataScript_HumanGrenadesDropped grenadesDropped;
  TuningDataScript_HumanKneeling kneeling;
  TuningDataScript_HumanAttractTurn attractTurn;
  TuningDataScript_HumanSpeechChance speechChance;
  TuningDataScript_HumanTargetBias targetBias;
  TuningDataScript_HumanSquad squad;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_LandMineWarning {
  float radius;
  float time;
  void ReflectorTag();
};
struct TuningDataScript_LandMineInstant {
  float radius;
  void ReflectorTag();
};
struct TuningDataScript_LandMineBlast {
  float force;
  float hotspot;
  float falloff;
  void ReflectorTag();
};

struct TuningDataScript_LandMine : TuningDataScript {
  TuningDataScript_LandMineWarning warning;
  TuningDataScript_LandMineInstant instant;
  TuningDataScript_LandMineBlast blast;
};

struct TuningDataScript_MiscellaneousParticleEffect {
  float genericParticleEffectsPoolSize;
  void ReflectorTag();
};
struct TuningDataScript_MiscellaneousDecals {
  float temporaryDecalsMaxOverlap;
  float temporaryDecalsCullTime;
  float decalDensityDrawnContext;
  float decalDensityNonDrawnContext;
  float decalRemovalSizeFactor;
  float decalRemovalOverlapFactor;
  void ReflectorTag();
};
struct TuningDataScript_MiscellaneousNavigator {
  float numberAngleToCheck;
  float lowLODRange;
  void ReflectorTag();
};
struct TuningDataScript_MiscellaneousCollisions {
  float autoRangeFactor0;
  float autoRangeFactor1;
  float autoRangeFactor2;
  void ReflectorTag();
};
struct TuningDataScript_MiscellaneousBlastCameraShake {
  float time;
  float scale;
  float maxAngleX;
  float maxAngleY;
  float maxAngleZ;
  void ReflectorTag();
};
struct TuningDataScript_MiscellaneousParticleEffects {
  float maxFlameSystems;
  float maxSmokeSystems;
  void ReflectorTag();
};

struct TuningDataScript_Miscellaneous : TuningDataScript {
  TuningDataScript_MiscellaneousParticleEffect particleEffect;
  TuningDataScript_MiscellaneousDecals decals;
  TuningDataScript_MiscellaneousNavigator navigator;
  TuningDataScript_MiscellaneousCollisions collisions;
  TuningDataScript_MiscellaneousBlastCameraShake blastCameraShake;
  TuningDataScript_MiscellaneousParticleEffects particleEffects;
};

struct TuningDataScript_MissileLauncherAmmo {
  float maxMissiles;
  void ReflectorTag();
};
struct TuningDataScript_MissileLauncherZoom {
  float zoomFactor;
  void ReflectorTag();
};
struct TuningDataScript_MissileLauncherShake {
  float fire1JoltTime;
  float fire1JoltAngle;
  float fire2JoltTime;
  float fire2JoltAngle;
  void ReflectorTag();
};
struct TuningDataScript_MissileLauncherMissileLaunch {
  float launchSpeed;
  float launchingTime;
  float pitchingAngle;
  void ReflectorTag();
};
struct TuningDataScript_MissileLauncherMissileFlight {
  float flightSpeed;
  float lifeTime;
  float guidance;
  float turnRate;
  void ReflectorTag();
};
struct TuningDataScript_MissileLauncherMissileBlast {
  float forceDamage;
  float heatDamage;
  float hotspot;
  float falloff;
  void ReflectorTag();
};

struct TuningDataScript_MissileLauncher : TuningDataScript {
  TuningDataScript_MissileLauncherAmmo ammo;
  TuningDataScript_MissileLauncherZoom zoom;
  TuningDataScript_MissileLauncherShake shake;
  TuningDataScript_MissileLauncherMissileLaunch missileLaunch;
  TuningDataScript_MissileLauncherMissileFlight missileFlight;
  TuningDataScript_MissileLauncherMissileBlast  missileBlast;
  TuningDataScriptCoreDamage coreDamage;
};

struct TuningDataScript_MoritiaMk2CarbineAmmo {
  float maxNumber;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2CarbinePrimary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2CarbineSecondary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2CarbineAIDrop {
  float minBullets;
  float maxBullets;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2Carbine : TuningDataScript {
  TuningDataScript_MoritiaMk2CarbineAmmo ammo;
  TuningDataScript_MoritiaMk2CarbinePrimary primary;
  TuningDataScriptShake fireShake;
  TuningDataScript_MoritiaMk2CarbineSecondary secondary;
  TuningDataScriptShake fireShake2;
  TuningDataScript_MoritiaMk2CarbineAIDrop aiDrop;
};

struct TuningDataScript_MoritiaMk2GrenadeAmmo {
  float maxNumber;
  float lowAmmo;
  float numGrenades;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2GrenadePrimary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2GrenadeGrenade {
  float launchVelY;
  float launchVelZ;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2GrenadeAIDrop {
  float minBullets;
  float maxBullets;
  float minGrenades;
  float maxGrenades;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2Grenade : TuningDataScript {
  TuningDataScript_MoritiaMk2GrenadeAmmo ammo;
  TuningDataScript_MoritiaMk2GrenadePrimary primary;
  TuningDataScript_MoritiaMk2GrenadeGrenade grenade;
  TuningDataScriptShake fireShake;
  TuningDataScriptJolt grenadeJolt;
  TuningDataScript_MoritiaMk2GrenadeAIDrop aiDrop;
};

struct TuningDataScript_MoritiaMk2ShotgunAmmo {
  float maxNumber;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2ShotgunPrimary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2ShotgunSecondary {
  float numBullets;
  float range;
  float spread;
  float strength;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2ShotgunAIDrop {
  float minBullets;
  float maxBullets;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2Shotgun : TuningDataScript {
  TuningDataScript_MoritiaMk2ShotgunAmmo ammo;
  TuningDataScript_MoritiaMk2ShotgunPrimary primary;
  TuningDataScript_MoritiaMk2ShotgunSecondary secondary;
  TuningDataScriptShake fire1Shake;
  TuningDataScriptJolt fire2Jolt;
  TuningDataScript_MoritiaMk2ShotgunAIDrop aiDrop;
};

struct TuningDataScript_MoritiaMk2ZoomAmmo {
  float maxNumber;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2ZoomPrimary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk2ZoomSecondary {
  float burstNumber;
  float burstPause;
  float fireRate;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  float zoomFactor;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2ZoomAIDrop {
  float minBullets;
  float maxBullets;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk2Zoom : TuningDataScript {
  TuningDataScript_MoritiaMk2ZoomAmmo ammo;
  TuningDataScript_MoritiaMk2ZoomPrimary primary;
  TuningDataScript_MoritiaMk2ZoomSecondary secondary;
  TuningDataScriptShake fire1Shake;
  TuningDataScriptShake fire2Shake;
  TuningDataScript_MoritiaMk2ZoomAIDrop aiDrop;
};

struct TuningDataScript_MoritiaMk4General {
  float clicksBeforeReload;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk4Ammo {
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk4Bullets {
  float maxNumber;
  float minBurst;
  float fireRate;
  float minReloadTime;
  float maxReloadTime;
  float range;
  float spread;
  float spreadFirst;
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk4Grenades {
  float maxNumber;
  void ReflectorTag();
};
struct TuningDataScript_MoritiaMk4Grenade {
  float launchVel;
  float launchVelZ;
  float drag;
  float blastforce;
  float blastHotspot;
  float blastFalloff;
  float proximityCheckTime;
  float proximityCheckRadius;
  float proximityCheckLife;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk4AIDrop {
  float minGrenades;
  float maxGrenades;
  void ReflectorTag();
};

struct TuningDataScript_MoritiaMk4 : TuningDataScript {
  TuningDataScript_MoritiaMk4General general;
  TuningDataScript_MoritiaMk4Ammo ammo;
  TuningDataScript_MoritiaMk4Bullets bullets;
  TuningDataScript_MoritiaMk4Grenades grenades;
  TuningDataScript_MoritiaMk4Grenade grenade;
  TuningDataScriptShake fireShake;
  TuningDataScriptJolt grenadeJolt;
  TuningDataScript_MoritiaMk4AIDrop aiDrop;
};

struct TuningDataScript_NukeLauncherMissile {
  float flightSpeed;
  float climbFactor;
  void ReflectorTag();
};

struct TuningDataScript_NukeLauncher : TuningDataScript {
  TuningDataScript_NukeLauncherMissile missile;
};

struct TuningDataScript_PlasmaDamageRequiredDuringFire {
  float damage;
  void ReflectorTag();
};
struct TuningDataScript_PlasmaBolt {
  float blastForce;
  float blastHotspot;
  float blastFalloff;
  float speed;
  void ReflectorTag();
};
struct TuningDataScript_PlasmaSpray {
  float targetCone;
  float sprayZScale;
  void ReflectorTag();
};
struct TuningDataScript_PlasmaCower {
  float holdTime;
  void ReflectorTag();
};

struct TuningDataScript_Plasma : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptDamage damageStrengthHead;
  TuningDataScriptDamage damageStrengthArse;
  TuningDataScriptDamage2 damage;
  TuningDataScript3FootImpact footImpact;
  TuningDataScript_PlasmaDamageRequiredDuringFire damageRequiredDuringFire;
  TuningDataScript_PlasmaBolt bolt;
  TuningDataScript_PlasmaSpray spray;
  TuningDataScript_PlasmaCower cover;
};

struct TuningDataScript_PlayerMovement {
  float runSpeed;
  float duckSpeed;
  float moveLag;
  float turnSpeed;
  float turnLag;
  float maxGradient;
  float slideGradient;
  float maxSlideSpeed;
  float stepHeight;
  float stepLenght;
  float sphereRadius;
  float heightStand;
  float heightDuck;
  float eyeHeight;
  float jumpVelUp;
  float duckRate;
  void ReflectorTag();
};
struct TuningDataScript_PlayerHealth {
  float regenerateRate0;
  float regenerateRate1;
  void ReflectorTag();
};
struct TuningDataScript_PlayerCrouch {
  float crouchAccuracy;
  float crouchBlastDamageReduction;
  void ReflectorTag();
};
struct TuningDataScript_PlayerShake {
  float shakeAmplitude;
  float shakeDuration;
  void ReflectorTag();
};
struct TuningDataScript_PlayerAmmoCapacity {
  float bullet;
  float grenade;
  float shotgun;
  float rocket;
  float missile;
  float slug;
  float handGrenade;
  void ReflectorTag();
};
struct TuningDataScript_PlayerMisc {
  float healthPickup;
  float criticalHealth;
  float fireDamage;
  void ReflectorTag();
};

struct TuningDataScript_PlayerFall {
  float hurtSpeed;
  float damageMultiplier;
  float minHeight;
  float maxHeight;
  float killPlaneHeight;
  void ReflectorTag();
};
struct TuningDataScript_PlayerFire {
  float checkInterval;
  void ReflectorTag();
};

struct TuningDataScript_Player : TuningDataScript {
  TuningDataScript_PlayerMovement movement;
  TuningDataScript_PlayerHealth health;
  TuningDataScript_PlayerCrouch crouch;
  TuningDataScript_PlayerShake shake;
  TuningDataScript_PlayerAmmoCapacity ammoCapacity;
  TuningDataScript_PlayerMisc misc;
  TuningDataScriptShake hitShake;
  TuningDataScript_PlayerFall fall;
  TuningDataScript_PlayerFire fire;
  TuningDataScriptPlayerStrength strength;
  TuningDataScriptPlayerShield shield;
};

struct TuningDataScript_RagdollDrag {
  float dragFactor;
  void ReflectorTag();
};
struct TuningDataScript_RagdollBlast {
  float blastFactor;
  void ReflectorTag();
};

struct TuningDataScript_Ragdoll : TuningDataScript {
  TuningDataScript_RagdollDrag drag;
  TuningDataScript_RagdollBlast blast;
};

struct TuningDataScript_RailgunAmmo {
  float maxNumber;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_RailgunBullet {
  float range;
  float spread;
  float strength;
  void ReflectorTag();
};
struct TuningDataScript_RailgunShockwave {
  float strength;
  float hotSpot;
  float falloff;
  float spacing;
  float timeDelay;
  void ReflectorTag();
};
struct TuningDataScript_RailgunZoomFactor {
  float stage1;
  float stage2;
  void ReflectorTag();
};


struct TuningDataScript_Railgun : TuningDataScript {
  TuningDataScript_RailgunAmmo ammo;
  TuningDataScript_RailgunBullet bullet;
  TuningDataScript_RailgunShockwave shockwave;
  TuningDataScript_RailgunZoomFactor zoomFactor;
  TuningDataScriptJolt joltUnZoomed;
  TuningDataScriptJolt joltZoom1;
  TuningDataScriptJolt joltZoom2;
};

struct TuningDataScript_RocketLauncherAmmo {
  float maxRockets;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_RocketLauncherFiring {
  float speedupNum;
  float delayMax;
  float delayMin;
  float joltTime;
  float joltAngle;
  void ReflectorTag();
};
struct TuningDataScript_RocketLauncherLockOn {
  float maxNumber;
  float maxRange;
  float maxAngleX;
  float maxAngleY;
  float showAngleX;
  float showAngleY;
  float joltTime;
  float joltAngle;
  void ReflectorTag();
};
struct TuningDataScript_RocketLauncherRocket {
  float noLockSpeed;
  float noLockLifeTime;
  float lockedSpeed;
  float lockedLifeTime;
  float turnRate;
  float weaveAngle;
  float weaveFrequency;
  void ReflectorTag();
};
struct TuningDataScript_RocketLauncherBlast {
  float strengthBlast;
  float strengthHeat;
  float hotspotRadius;
  float falloffRadius;
  void ReflectorTag();
};
struct TuningDataScript_RocketLauncherAIDrop {
  float minRockets;
  float maxRockets;
  void ReflectorTag();
};

struct TuningDataScript_RocketLauncher : TuningDataScript {
  TuningDataScript_RocketLauncherAmmo ammo;
  TuningDataScript_RocketLauncherFiring firing;
  TuningDataScript_RocketLauncherLockOn lockOn;
  TuningDataScript_RocketLauncherRocket rocket;
  TuningDataScript_RocketLauncherBlast blast;
  TuningDataScript_RocketLauncherAIDrop aiDrop;
};

struct TuningDataScript_ShotgunAmmo {
  float maxShells;
  float lowAmmo;
  void ReflectorTag();
};
struct TuningDataScript_ShotgunPrimary {
  float numberShells;
  float numberRayTests;
  float rayTestRange;
  float rayTestSpread;
  float rayTestStrength;
  float blastRange;
  float blastAngle;
  float blastStrength;
  void ReflectorTag();
};
struct TuningDataScript_ShotgunPrimaryJolt {
  float time;
  float angle;
  void ReflectorTag();
};
struct TuningDataScript_ShotgunSecondary {
  float numberShells;
  float numberRayTests;
  float rayTestRange;
  float rayTestSpread;
  float rayTestStrength;
  float blastRange;
  float blastAngle;
  float blastStrength;
  void ReflectorTag();
};
struct TuningDataScript_ShotgunSecondaryJolt {
  float time;
  float angle;
  void ReflectorTag();
};
struct TuningDataScript_ShotgunAIDrop {
  float minShells;
  float maxShells;
  void ReflectorTag();
};

struct TuningDataScript_Shotgun : TuningDataScript {
  TuningDataScript_ShotgunAmmo ammo;
  TuningDataScript_ShotgunPrimary primary;
  TuningDataScript_ShotgunPrimaryJolt primaryJolt;
  TuningDataScript_ShotgunSecondary secondary;
  TuningDataScript_ShotgunSecondaryJolt secondaryJolt;
  TuningDataScript_ShotgunAIDrop aiDrop;
};

struct TuningDataScript_StaticGunDoubleGeneral {
  float bulletStrength;
  float fireRate;
  float zoomFactor;
  float zoomRate;
  void ReflectorTag();
};
struct TuningDataScript_StaticGunDoubleRotation {
  float rateHeading;
  float ratePitch;
  float gunLag;
  void ReflectorTag();
};
struct TuningDataScript_StaticGunDoubleTemerature {
  float firingDelta;
  float coolingRate;
  float overheatTime;
  void ReflectorTag();
};

struct TuningDataScript_StaticGunDoubleAIParameters {
  float reTargetTime;
  float rateHeading;
  float ratePitch;
  void ReflectorTag();
};

struct TuningDataScript_StaticGunDouble : TuningDataScript {
  TuningDataScript_StaticGunDoubleGeneral general;
  TuningDataScript_StaticGunDoubleRotation rotation;
  TuningDataScript_StaticGunDoubleTemerature temerature;
  TuningDataScriptShake fireShake;
  TuningDataScript_StaticGunDoubleAIParameters aiParameters;
};

struct TuningDataScript_TankerBullet {
  float head;
  float rest;
  void ReflectorTag();
};
struct TuningDataScript_TankerBlast {
  float head;
  float rest;
  void ReflectorTag();
};
struct TuningDataScript_TankerSpotting {
  float rangeMin;
  float rangeMax;
  float cone;
  float chance;
  float torchSightModifier;
  void ReflectorTag();
};
struct TuningDataScript_TankerStomp {
  float strength;
  float hotspot;
  float falloff;
  void ReflectorTag();
};
struct TuningDataScript_TankerFire {
  float damageDelay;
  float strength;
  float hotspot;
  float falloff;
  void ReflectorTag();
};
struct TuningDataScript_TankerHealth {
  float valRetract;
  void ReflectorTag();
};

struct TuningDataScript_Tanker : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage2 damage;
  TuningDataScript_TankerBullet bullet;
  TuningDataScript_TankerBlast blast;
  TuningDataScript_TankerSpotting spotting;
  TuningDataScript_TankerStomp stomp;
  TuningDataScript_TankerFire fire;
  TuningDataScript_TankerHealth health;
};

struct TuningDataScript_TankerBabyAttack {
  float fireBurstRange;
  float blastForce;
  float blastHotSpot;
  float blastFalloff;
  float boltSpeed;
  float forceBarge;
  void ReflectorTag();
};
struct TuningDataScript_TankerBabyDamageStrength {
  float threshold;
  void ReflectorTag();
};

struct TuningDataScript_TankerBabyAccuracy : TuningDataScriptAccuracy {
  void ReflectorTag();
};

struct TuningDataScript_TankerBaby : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScript_TankerBabyAttack attack;
  TuningDataScript_TankerBabyDamageStrength damageStrength;
  TuningDataScript2FootImpact footImpact;
  TuningDataScriptDamage damageStrengthHead;
  TuningDataScriptDamage2 damage;
  TuningDataScriptNetworkStrategy networkStrategy;
  TuningDataScript_TankerBabyAccuracy accuracy;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
};

struct TuningDataScript_TigerDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_TigerAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_TigerStrength {
  float bulletNerve;
  float bulletHead;
  float bulletLegs;
  float blast;
  float heat;
  float sonic;
  float cosmeticShieldsPierce;
  void ReflectorTag();
};
struct TuningDataScript_TigerHealth {
  float cosmeticShields;
  void ReflectorTag();
};
struct TuningDataScript_TigerStrategy {
  float evasionChance;
  float evasionDist;
  void ReflectorTag();
};
struct TuningDataScript_TigerDeath {
  float deltaHealthForGib;
  float bodyMovementFactor;
  void ReflectorTag();
};

struct TuningDataScript_Tiger : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScript_TigerDefence defence;
  TuningDataScript_TigerAttack attack;
  TuningDataScript_TigerStrength strength;
  TuningDataScript_TigerHealth health;
  TuningDataScript_TigerStrategy strategy;
  TuningDataScript_TigerDeath death;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire2 fire;
  TuningDataScriptSpotting2 idle;
  TuningDataScriptSpotting3 alert;
  TuningDataScriptSpotting2 spotting;
};

struct TuningDataScript_TigerShardDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_TigerShardAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_TigerShardStrength {
  float bulletNerve;
  float bulletHead;
  float bulletLegs;
  float blast;
  float heat;
  float sonic;
  void ReflectorTag();
};
struct TuningDataScript_TigerShardWeapon {
  float meleeRange;
  float innerRange;
  float outerRange;
  float fireAngle;
  float coneSpreadX;
  float coneSpreadY;
  float coneSpreadZ;
  float coneAngle;
  float coneNumShards;
  float damage;
  void ReflectorTag();
};
struct TuningDataScript_TigerShardStrategy {
  float idealDist;
  float evasionDistance;
  float evasionChance;
  float meleeAttackDist;
  float berserkHealth;
  float shortFireDist;
  float shortFireChance;
  void ReflectorTag();
};
struct TuningDataScript_TigerShardBolt {
  float speed;
  float life;
  void ReflectorTag();
};

struct TuningDataScript_TigerShardAccuracy : TuningDataScriptAccuracy {
  void ReflectorTag();
};

struct TuningDataScript_TigerShard : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScript_TigerShardDefence defence;
  TuningDataScript_TigerShardAttack attack;
  TuningDataScript_TigerShardStrength strength;
  TuningDataScript_TigerShardWeapon weapon;
  TuningDataScript_TigerShardStrategy strategy;
  TuningDataScript_TigerShardBolt bolt;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire2 fire;
  TuningDataScriptSpotting2 idle;
  TuningDataScriptSpotting3 alert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
  TuningDataScript_TigerShardAccuracy accuracy;
};

struct TuningDataScript_TigerSpitDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitStrength {
  float bulletNerve;
  float bulletHead;
  float bulletLegs;
  float blast;
  float heat;
  float sonic;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitWeapon {
  float meleeRange;
  float innerRange;
  float outerRange;
  float spitAngle;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitStrategy {
  float idealDist;
  float evasionDistance;
  float evasionChance;
  float meleeAttackDist;
  float berserkHealth;
  float shotSpitDist;
  float shotSpitChance;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitAccuracy {
  float minimumVariance;
  float maximumVariance;
  float number_Of_Intervals;
  float spitPredictionTime;
  void ReflectorTag();
};
struct TuningDataScript_TigerSpitBolt {
  float blastForce;
  float blastHotspot;
  float blastFalloff;
  float speed;
  void ReflectorTag();
};

struct TuningDataScript_TigerSpit : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScript_TigerSpitDefence defence;
  TuningDataScript_TigerSpitAttack attack;
  TuningDataScript_TigerSpitStrength strength;
  TuningDataScript_TigerSpitWeapon weapon;
  TuningDataScript_TigerSpitStrategy strategy;
  TuningDataScript_TigerSpitAccuracy accuracy;
  TuningDataScript_TigerSpitBolt bolt;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire2 fire;
  TuningDataScriptSpotting2 idle;
  TuningDataScriptSpotting3 alert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_WarriorDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRagdoll {
  float density;
  void ReflectorTag();
};
struct TuningDataScript_WarriorAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_WarriorStrength {
  float bulletNerveSoft;
  float bulletNerveHard;
  float bulletHeadSoft;
  float bulletHeadHard;
  float bulletLegsSoft;
  float bulletLegsHard;
  float slash;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiOps;
  float sonic;
  float cosmeticShields;
  void ReflectorTag();
};
struct TuningDataScript_WarriorHealth {
  float cosmeticShields;
  void ReflectorTag();
};
struct TuningDataScript_WarriorDeath {
  float deltaHealthForGib;
  float bodyMovementFactor;
  void ReflectorTag();
};

struct TuningDataScript_Warrior : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScript_WarriorDefence defence;
  TuningDataScript_WarriorRagdoll ragdoll;
  TuningDataScript_WarriorAttack attack;
  TuningDataScript_WarriorStrength strength;
  TuningDataScript_WarriorHealth health;
  TuningDataScript_WarriorDeath death;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire2 fire;
  TuningDataScriptSpotting2 idle;
  TuningDataScriptSpotting3 alert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_WarriorRoyalDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalRagdoll {
  float density;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalLegPunches {
  float minLegVelocity;
  float colSphereRadius;
  float impactPunchForce;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalFootImpact {
  float punchMultiplier;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalStrength {
  float eyeShieldPierceSoft;
  float eyeShieldPierceHard;
  float eyePierceSoft;
  float eyePierceHard;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiOps;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalHealth {
  float eyeShieldLeft;
  float eyeShieldRight;
  float eyeLeft;
  float eyeRight;
  float cosmeticShields;
  float mandibleShields;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalDamageThreshold {
  float threshold;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalStrategy {
  float outOfDistanceAttackRoarChance;
  float outOfDistanceAttackRoarRange;
  float randomRoarChance;
  float randomRoarMinDistance;
  float facingTargetAngle;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalMisc {
  float eyeRadius;
  void ReflectorTag();
};

struct TuningDataScript_WarriorRoyal : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
  TuningDataScript_WarriorRoyalDefence defence;
  TuningDataScript_WarriorRoyalRagdoll ragdoll;
  TuningDataScript_WarriorRoyalAttack attack;
  TuningDataScript_WarriorRoyalLegPunches legPunches;
  TuningDataScript_WarriorRoyalFootImpact footImpact;
  TuningDataScript_WarriorRoyalStrength strength;
  TuningDataScript_WarriorRoyalHealth health;
  TuningDataScript_WarriorRoyalDamageThreshold damageThreshold;
  TuningDataScript_WarriorRoyalStrategy strategy;
  TuningDataScript_WarriorRoyalMisc misc;
  TuningDataScriptSpotting2 spottingIdle;
  TuningDataScriptSpotting3 spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_WarriorRoyalXDefence {
  float percentageChance;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXRagdoll {
  float density;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXAttack {
  float strength;
  float predictionSpeed;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXLegPunches {
  float minLegVelocity;
  float colSphereRadius;
  float impactPunchForce;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXFootImpact {
  float punchMultiplier;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXStrength {
  float eyeShieldPierceSoft;
  float eyeShieldPierceHard;
  float eyePierceSoft;
  float eyepierceHard;
  float punch;
  float blast;
  float heat;
  float corrosive;
  float electricity;
  float psiOps;
  float annoyedRearUpSoft;
  float annoyedRearUpHard;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXDamageThreshold {
  float threshold;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXHealth {
  float eyeShieldLeft;
  float eyeShieldRight;
  float eyeLeft;
  float eyeRight;
  float cosmeticShields;
  float rearUpDamageTrigger;
  float mandibleShields;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXStrategy {
  float sonicRadialRoarChance;
  float sonicRadialRoarDistance;
  float sonicRoarChance;
  float sonicRoarDistance;
  float jetFireChance;
  float blastDelayTime;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXDamage {
  float nonPlayerFactor;
  float sonicBlastIntensity;
  void ReflectorTag();
};
struct TuningDataScript_WarriorRoyalXMisc {
  float eyeRadius;
  void ReflectorTag();
};

struct TuningDataScript_WarriorRoyalX : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScript_WarriorRoyalXDefence Defence;
  TuningDataScript_WarriorRoyalXRagdoll Ragdoll;
  TuningDataScript_WarriorRoyalXAttack attack;
  TuningDataScript_WarriorRoyalXLegPunches legPunches;
  TuningDataScript_WarriorRoyalXFootImpact footImpact;
  TuningDataScript_WarriorRoyalXStrength strength;
  TuningDataScript_WarriorRoyalXDamageThreshold damageThreshold;
  TuningDataScript_WarriorRoyalXHealth health;
  TuningDataScript_WarriorRoyalXStrategy strategy;
  TuningDataScript_WarriorRoyalXDamage damage;
  TuningDataScript_WarriorRoyalXMisc misc;
  TuningDataScriptFire fire;
  TuningDataScriptSpotting2 spottingIdle;
  TuningDataScriptSpotting3 spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_RhinoDamageStrengthThreshold {
  float threshold;
  void ReflectorTag();
};
struct TuningDataScript_RhinoAttack {
  float chargeForceFront;
  float chargeForceTop;
  float attackStill;
  void ReflectorTag();
};
struct TuningDataScript_RhinoStrategy {
  float chargePastDistance;
  float chargeHeadDipDistance;
  float slideDistance;
  float slideHoldTime;
  void ReflectorTag();
};

struct TuningDataScript_Rhino : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScriptDamage damageStrengthHead;
  TuningDataScriptDamage damageStrengthRear;
  TuningDataScriptDamage2 damage;
  TuningDataScript2FootImpact footImpact;
  TuningDataScript_RhinoDamageStrengthThreshold damageStrengthThreshold;
  TuningDataScript_RhinoAttack attack;
  TuningDataScript_RhinoStrategy strategy;
  TuningDataScriptNavigator navigator;
  TuningDataScriptNavigatorSpeed navigatorSpeedData0;
  TuningDataScriptNavigatorSpeed navigatorSpeedData1;
  TuningDataScriptNavigatorSpeed navigatorSpeedData2;
};

struct TuningDataScript_SentinelAttack {
  float zapDistance;
  float flashFalloffMin;
  float flashCutoffMax;
  float flashIntensity;
  void ReflectorTag();
};

struct TuningDataScript_Sentinel : TuningDataScript {
  TuningDataScriptSpottingTargetBias spottingTargetBias;
  TuningDataScriptSpotting spottingIdle;
  TuningDataScriptSpotting spottingAlert;
  TuningDataScriptSpotting2 spotting;
  TuningDataScript_SentinelAttack attack;
  TuningDataScriptStrength strength;
  TuningDataScriptDamage2 damage;
  TuningDataScriptFire fire;
};
