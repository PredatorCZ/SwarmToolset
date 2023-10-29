#pragma once
#include "core.hpp"
#include <map>

enum class ShadowGeneration {
  ALL_MATERIALS_SHADOW,
  NO_MATERIALS_SHADOW,
  PER_MATERIAL_SHADOW,
};

enum class ModelType {
  Generic,
  Terrain,
  Instanced,
  FirstPerson,
};

struct ResourceObjectModelMaterial {
  std::string key;
  ResourceRef value;
  void ReflectorTag();
  void ReflectorMap();
};

struct ResourceObjectModel : ResourcePack {
  AFileInfo fileName;
  ShadowGeneration shadowGeneration;
  bool animated;
  std::vector<ResourceObjectModelMaterial> materials;
  std::vector<ResourceObjectModelMaterial> physicalMaterials;
  ResourceRef defaultPhysicalMaterial;
  ResourceRef collidableResource;
  ResourceArray animationSets;
  std::vector<std::string> boneNames;
  std::vector<std::string> debugNumComponents;
  ModelType modelType;
  ResourceRef baseModelAnimSets;
};

struct ResourceObjectAnimationSet : ResourcePack {
  std::string animationType;// TODO string so far
  ResourceArray animations;
  ResourceRef refModel;
};

struct ResourceObjectAnimationCompression {
  float scaleTolerance;
  float rotateTolerance;
  float positionTolerance;
  void ReflectorTag();
};

struct ResourceObjectAnimation : ResourcePack {
  AFileInfo fileName;
  float length;
  float soundProbability;
  ResourceRef sound;
  ResourceArray soundList;
  uint32 soundBone;
  ResourceRef animationSet;
  std::string boneNameExtension;
  ResourceObjectAnimationCompression compression;
};

struct ResourceAmmoPickupAmount {
  uint32 bullet;
  uint32 grenade;
  uint32 shotgun;
  uint32 rocket;
  uint32 missile;
  uint32 slug;
  uint32 handgrenade;
  void ReflectorTag();
};

struct ResourceAmmoPickup : ResourcePack {
  ResourceRef model;
  ResourceAmmoPickupAmount pickupAmount;
};

struct ResourceObjectDropPod : ResourcePack {
  ResourceRef soundDescentResource;
  ResourceRef soundBurstResource;
  ResourceArray dataKeys;
  float podDensity;
  float blastVal;
};

struct ResourceObjectDropPodKey : ResourcePack {
  float keyTime;
  float shake;
};

struct ResourceObjectRocketTargetInfo : ResourcePack {
  ResourceArray nodes;
};

struct ResourceObjectRocketTargetNode : ResourcePack {
  std::string boneName;
  Vector nodePos;
  float nodeSize;
  float testSize;
};

struct ResourceDecal : ResourcePack {
  AFileInfo texDiffuse;
  AFileInfo texNormal;
  Color ambient;
  Color diffuse;
  Color specular;
  float minU;
  float minV;
  float maxU;
  float maxV;
  float sizeAverage;
  float sizeRange;
  float lifeTime;
  float fadeTime;
  Color iconColour;
};

struct ResourceDestructableObjectDamageStrength {
  float PIERCESOFT;
  float PIERCEHARD;
  float SLASH;
  float PUNCH;
  float BLAST;
  float HEAT;
  float CORROSIVE;
  float ELECTRICITY;
  float PSIOPS;
  void ReflectorTag();
};

struct ResourceDestructableObjectPiecesMovement {
  float pieceDensity;
  float blastStrength;
  float blastExplode;
  float blastExplodeRadius;
  float flamingBits;
  void ReflectorTag();
};

struct ResourceDestructableObject : ResourcePack {
  ResourceRef modelWhole;
  ResourceRef modelDead;
  ResourceRef modelPieces;
  ResourceRef soundDeath;
  ResourceDestructableObjectDamageStrength damageStrength;
  bool dynamic;
  float setOnFireAtHealthPercent;
  float selfDamageWhenOnFire;
  ResourceDestructableObjectPiecesMovement piecesMovement;
};

struct ResourceObjectSFXBabyPlasma : ResourcePack {
  ResourceRef soundBoltFire;
  ResourceRef soundBoltExplode;
  float scaleFactor;
  ResourceRef materialHead;
  ResourceRef materialRear;
  ResourceRef materialBody;
};

struct ResourceObjectSFXBlaster : ResourcePack {
  ResourceRef soundDeath;
  ResourceRef material;
};

struct ResourceObjectSFXBomber : ResourcePack {
  ResourceRef soundGlobalEngine;
  ResourceRef soundGlobalAscend;
  ResourceRef soundGlobalDescend;
  ResourceRef soundGlobalHover;
  ResourceRef soundGlobalFlyBy;
};

struct ResourceObjectSFXCliffMite : ResourceObjectSFXBlaster {};
struct ResourceObjectSFXChariot : ResourceObjectSFXBlaster {};
struct ResourceObjectSFXDropshipGrunt : ResourceObjectSFXBomber {};
struct ResourceObjectSFXDropshipCargo : ResourceObjectSFXBomber {};
struct ResourceObjectSFXDropshipMarauder : ResourceObjectSFXBomber {};

struct ResourceObjectSFXElectricFence : ResourcePack {
  ResourceRef soundElectricFence;
  ResourceRef soundElectricFencePost;
};

struct ResourceObjectSFXFireball : ResourcePack {
  ResourceRef soundBoltFire;
  ResourceRef soundBoltExplode;
};

struct ResourceObjectSFXHopperFirefly : ResourcePack {
  ResourceRef soundFireSpurt;
  ResourceRef material;
};

struct ResourceObjectSFXHuman : ResourcePack {
  ResourceRef soundGibBounce;
  ResourceRef materialMPMarauder;
  ResourceRef materialMPMarauderShield;
};

struct ResourceObjectSFXHandGrenadeMouthTiming {
  float ONStart;
  float ONEnd;
  float LINEStart;
  float LINEEnd;
  float FOURStart;
  float FOUREnd;
  float THREEStart;
  float THREEEnd;
  float TWOStart;
  float TWOEnd;
  float ONEStart;
  float ONEEnd;
  float ARMEDStart;
  float ARMEDEnd;
  float EMStart;
  float EMEnd;
  float ERStart;
  float EREnd;
  float GENStart;
  float GENEnd;
  float CYStart;
  float CYEnd;
  float SHUTStart;
  float SHUTEnd;
  float DOWNStart;
  float DOWNEnd;
  void ReflectorTag();
};

struct ResourceObjectSFXHandGrenade : ResourcePack {
  ResourceRef soundInHand;
  ResourceRef soundThrown;
  float activateTime;
  float flashFrequency;
  float brightnessOff;
  float brightnessActivate;
  float brightnessOn;
  float brightnessFlash0;
  float brightnessFlash1;
  float mouthTalkFrequency;
  float mouthWaveFrequency;
  float talkTimeActivate;
  float talkTimeDeactivate;
  ResourceObjectSFXHandGrenadeMouthTiming mouthTiming;// : {}
};

struct ResourceObjectSFXHopper : ResourcePack {
  ResourceRef material;
};

struct ResourceObjectSFXMissile : ResourcePack {
  ResourceRef soundShot;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
  ResourceRef soundExplode;
  ResourceRef modeSwitch1;
  ResourceRef modeSwitch2;
  ResourceRef guidanceTone;
  ResourceRef engine;
};

struct ResourceObjectSFXMissileBomberBomb : ResourcePack {
  ResourceRef soundGlobalEngine;
  ResourceRef soundGlobalAscend;
  ResourceRef soundGlobalDescend;
  ResourceRef soundGlobalHover;
};

struct ResourceObjectSFXMoritiaMk2Carbine : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundTailoffSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
};

struct ResourceObjectSFXMoritiaMk2Grenade : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
};

struct ResourceObjectSFXMoritiaMk2Shotgun : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
};

struct ResourceObjectSFXMoritiaMk2Zoom : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundTailoffSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
  ResourceRef soundZoomIn;
  ResourceRef soundZoomOut;
};

struct ResourceObjectSFXPlasma : ResourcePack {
  ResourceRef soundBoltFire;
  ResourceRef soundBoltExplode;
  Color lightColour;
  Color lightRange;
  ResourceRef materialHead;
  ResourceRef materialRear;
  ResourceRef materialBody;
  ResourceRef materialHeadCower;
};

struct ResourceObjectSFXMoritiaMk4 : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
  ResourceRef soundVent;
  ResourceRef soundVentShort;
  ResourceRef soundGrenadeExplode;
};

struct ResourceObjectSFXPlayerSoundEffects {
  ResourceRef psfxt_INVENTORYPICKUP;
  ResourceRef psfxt_HOPPERATTACK;
  ResourceRef psfxt_WARRIORATTACK;
  ResourceRef psfxt_TIGERATTACK;
  ResourceRef psfxt_TANKERFLAMEATTACK;
  ResourceRef psfxt_HEALTHCRITICAL;
  ResourceRef psfxt_WEAPONSWITCH;
  ResourceRef psfxt_FOOTFALLLADDERL;
  ResourceRef psfxt_FOOTFALLLADDERR;
  ResourceRef psfxt_JUMPTAKEOFF;
  ResourceRef psfxt_JUMPLAND;
  ResourceRef psfxt_HITBLAST;
  ResourceRef psfxt_HITBULLET;
  ResourceRef psfxt_SHIELDATZERO;
  ResourceRef psfxt_SHIELDREGENSTART___NOT_USED___;
  ResourceRef psfxt_SHIELDREGENERATE;
  ResourceRef psfxt_SHIELDREGENEND___NOT_USED___;
  void ReflectorTag();
};

struct ResourceObjectSFXPlayerHitEffectColours {
  Color shield;
  Color health;
  Color green;
  void ReflectorTag();
};

struct ResourceObjectSFXPlayerDamageSoundEffects {
  ResourceRef sfxPierceSoft;
  ResourceRef sfxPierceHard;
  ResourceRef sfxSlash;
  ResourceRef sfxPunch;
  ResourceRef sfxBlast;
  ResourceRef sfxHeat;
  ResourceRef sfxCorrosive;
  ResourceRef sfxElectricity;
  ResourceRef sfxPsiOps;
  ResourceRef sfxLight;
  ResourceRef sfxSonic;
  void ReflectorTag();
};

struct ResourceObjectSFXPlayer : ResourcePack {
  ResourceObjectSFXPlayerSoundEffects soundEffects;
  ResourceObjectSFXPlayerHitEffectColours hitEffectColours;
  ResourceObjectSFXPlayerDamageSoundEffects damageSoundEffects;
};

struct ResourceObjectSFXProjectileFlare : ResourcePack {
  ResourceRef soundProjectileFlare;
  ResourceRef soundProjectileFlarePop;
  Color lightColour;
  float lightRange;
  float rangePart1;
  float rangePart2;
  float frequency;
  float randomPart2;
  float launchSpeed;
  float fallRate;
  float waveMagnitude;
  float range1PcentAtT;
  float range1T;
  float flickerMinOn;
  float flickerMaxOn;
  float flickerMinOff;
  float flickerMaxOff;
};

struct ResourceObjectSFXRailGun : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
  ResourceRef soundZoomIn;
  ResourceRef soundZoomOut;
};

struct ResourceObjectSFXRhino : ResourcePack {
  ResourceRef materialHead;
  ResourceRef materialRear;
  ResourceRef materialBody;
};

struct ResourceObjectSFXHopperRippler : ResourcePack {
  ResourceRef material;
  bool lightOn;
  Color lightColour;
  float lightRange;
};

struct ResourceObjectSFXRocket : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
  ResourceRef soundExplode;
  ResourceRef soundLockOn;
};

struct ResourceObjectSFXSentinel : ResourcePack {
  ResourceRef soundDeath;
  ResourceRef material;
};

struct ResourceObjectSFXShotgun : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundShotSecondary;
  ResourceRef soundEmpty;
  ResourceRef soundReload;
};

struct ResourceObjectSFXStaticGunDouble : ResourcePack {
  ResourceRef soundShotPrimary;
  ResourceRef soundTailoffPrimary;
};

struct ResourceObjectSFXTanker : ResourcePack {
  ResourceRef materialHead;
  ResourceRef materialRear;
  ResourceRef materialBody;
};

struct ResourceObjectSFXTankerBaby : ResourcePack {
  ResourceRef materialHead;
  ResourceRef materialRear;
  ResourceRef materialBody;
};

struct ResourceObjectSFXTigerShard : ResourcePack {
  ResourceRef materialBody;
  ResourceRef materialShields;
};

struct ResourceObjectSFXTigerSpit : ResourcePack {
  ResourceRef materialBody;
  ResourceRef materialShields;
};

struct ResourceObjectSFXWarrior : ResourcePack {
  ResourceRef material;
};

struct ResourceObjectSFXWarriorRoyal : ResourcePack {
  ResourceRef materialShields;
  ResourceRef materialEyes;
  ResourceRef materialRicochet;
};

struct ResourceObjectSFXWarriorRoyalX : ResourcePack {
  ResourceRef materialShields;
  ResourceRef materialEyes;
  ResourceRef materialRicochet;
  ResourceRef materialDeathBone;
};
