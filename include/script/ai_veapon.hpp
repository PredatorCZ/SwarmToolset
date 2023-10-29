#pragma once
#include "quicksave/ai_weapon.hpp"

struct AIStaticGunDoubleGunParameters {
  float range;
  float spread;
  float angleRangeHeading;
  float angleRangePitch;
  void ReflectorTag();
};

struct AIStaticGunDoubleAIParameters {
  float engageRange;
  float hitRate;
  void ReflectorTag();
};

struct AIStaticGunDouble : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  bool switchedOn;
  AIStaticGunDoubleGunParameters gunParameters;
  AIStaticGunDoubleAIParameters aiParameters;
  bool destroyed;
  AIStaticGunDoubleQuicksave atStaticGunDoubleQuicksave;
  AIStaticGunDoubleQuicksave2 quicksave;
  StaticGunQuicksave staticGunQuicksave;
  Resource flash1;
  Resource flash2;
  Resource tracer;
  bool reloadAfterXMisfires;
};

struct AIStaticNukeLauncher : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  float viewZoom;
  Vector viewOffset;
  bool switchedOn;
  uint32 ammo;
  ResourceRef target;
  ResourceRef useActions;
  ResourceRef fireActions;
  ResourceRef impactActions;
  float missileSpeed;
  float missileClimb;
};

enum AIPROJ {
  AIPROJ_BABYPLASMABOLT,
  AIPROJ_BABYTANKERFIREBALL,
  AIPROJ_PLASMABOLT,
  AIPROJ_FLARE,
  AIPROJ_BOMB,
  AIPROJ_NAPALM,
  AIPROJ_TIGERSHARD,
  AIPROJ_TIGERSPIT,
  AIPROJ_BLASTER,
  AIPROJ_CLIFFMITE,
  AIPROJ_NUM,
};

struct AIProjectileLauncher : WorldObject {
  bool active;
  AIEntityGenericAABB aabb;
  AIPROJ type;
  ResourceRef target;
  float minTime;
  float maxTime;
  float launchAngle;
  float noTargetLaunchHeading;
  float noTargetLaunchDistance;
  AIProjectileLauncherQuicksave aiProjectileLauncherQuicksave;
};

struct AIWeaponShotgun : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoShells;
};

struct AIWeaponRailgun : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoSlugs;
  AIWeaponRailgunQuicksave aiWeaponRailgunQuicksave;
};

struct AIWeaponRocket : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoRocket;
  AIWeaponRocketQuicksave aiWeaponRocketQuicksave;
};

struct AIWeaponMoritiaMk2Carbine : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoBullet;
  AIWeaponMoritiaMk2CarbineQuicksave aiWeaponMoritiaMk2CarbineQuicksave;
};

struct AIWeaponMoritiaMk2Shotgun : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoBullet;
  AIWeaponMoritiaMk2CarbineQuicksave aiWeaponMoritiaMk2ShotgunQuicksave;
};

struct AIWeaponMissile : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  AIWeaponMissileQuicksave aiWeaponMissileQuicksave;
};

struct AIWeaponMoritiaMk2Grenade : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 bulletAmmo;
  uint32 grenadeAmmo;
  AIWeaponMoritiaMk2CarbineQuicksave aiWeaponMoritiaMk2GrenadeQuicksave;
  int32 reloadAfterXMisfires;
  AIWeaponMoritiaMk2CarbineQuicksave mk2GrenadeQuicksave;
  AIWeaponMoritiaMk2GrenadeQuicksave quicksave;
};

struct AIWeaponMoritiaMk2Zoom : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoBullet;
  AIWeaponMoritiaMk2ZoomQuicksave aiWeaponMoritiaMk2ZoomQuicksave;
};

struct AIWeaponMoritiaMk4 : ModelDetailDynamic {
  AIWeaponQuicksave aiWeaponQuicksave;
  uint32 ammoGrenade;
  AIWeaponMoritiaMk4Quicksave aiWeaponMoritiaMk4Quicksave;
  int32 reloadAfterXMisfires;
  AIWeaponMoritiaMk4Quicksave2 quicksave;
  AIWeaponMoritiaMk4Quicksave mk4Quicksave;
};
