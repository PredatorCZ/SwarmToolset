#pragma once
#include "script/core.hpp"

struct AIWeaponQuicksave {
  AIWEAPMODE mode;
  AIWEAPMODE desMode;
  ResourceRef pTarget;
  uint32 pAnim;
  float modeStartTime;
  float modeEndTime;
  void ReflectorTag();
};

struct StaticGunQuicksave {
  float gunHeading;
  float gunPitch;
  float viewHeading;
  float viewPitch;
  float modeStartTime;
  float modeEndTime;
  float desZoom;
  float zoom;
  float targetingTime;
  float temperature;
  float overHeatTime;
  bool bParked;
  uint32 barrelNum;
  bool destroyed;
  void ReflectorTag();
};

struct AIStaticGunDoubleQuicksave : StaticGunQuicksave {
  Matrix baseMatrix;
  Matrix gunMatrix0;
  void ReflectorTag();
};

struct AIStaticGunDoubleQuicksave2 {
  AIWEAPMODE mode;
  AIWEAPMODE desMode;
  float modeStartTime;
  ResourceRef pTarget;
  float modeEndTime;
  uint32 pAnim;
  void ReflectorTag();
};

struct AIProjectileLauncherQuicksave {
  float nextFireTime;
  void ReflectorTag();
};

struct AIWeaponRailgunQuicksave {
  bool bDesReload;
  uint32 zoomStage;
  bool modeStartZoom;
  bool modeEndZoom;
  void ReflectorTag();
};

struct AIWeaponRocketQuicksave {
  uint32 burstNum;
  void ReflectorTag();
};

struct AIWeaponMoritiaMk2CarbineQuicksave {
  uint32 burstNum;
  void ReflectorTag();
};

struct AIWeaponMissileQuicksave {
  uint32 ammoMissile;
  bool bDesReload;
  ResourceRef pMissile;
  void ReflectorTag();
};

struct AIWeaponMoritiaMk2GrenadeQuicksave {
  uint32 pAnim;
  float modeEndTime;
  ResourceRef pTarget;
  float modeStartTime;
  AIWEAPMODE desMode;
  AIWEAPMODE mode;
  void ReflectorTag();
};

struct AIWeaponMoritiaMk4Quicksave {
  int32 ammoBullet;
  int32 burstNum;
  float lastLoadTime;
  bool bNeedToVent;
  void ReflectorTag();
};

struct AIWeaponMoritiaMk4Quicksave2 {
  AIWEAPMODE mode;
  AIWEAPMODE desMode;
  float modeStartTime;
  ResourceRef pTarget;
  float modeEndTime;
  int32 pAnim;
  void ReflectorTag();
};

struct AIWeaponMoritiaMk2ZoomQuicksave {
  uint32 burstNum;
  bool bDesReload;
  void ReflectorTag();
};
