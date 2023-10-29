#pragma once
#include "enum_share.hpp"
#include "quicksave/ai_objects.hpp"

struct AICamera : AIWorldObject {
  float movementSpeed;
  float rotateSpeed;
  ResourceRef target;
  bool followTarget;
  AICameraQuicksave cameraQuicksave;
};

struct AILandMine : Resource {
  bool active;
  float posX;
  float posY;
  float posZ;
  AILandMineQuicksave aiLandMineQuicksave;
};

struct AISwitchSoundEffects {
  ResourceRef unlock;
  ResourceRef lock;
  ResourceRef useOn;
  ResourceRef useOff;
  void ReflectorTag();
};

struct AISwitchStateActions {
  ResourceRef off;
  ResourceRef switchingOn;
  ResourceRef on;
  ResourceRef switchingOff;
  void ReflectorTag();
};

struct AISwitch : ModelDetailDynamic {
  ResourceRef animSwitchingOn;
  ResourceRef animSwitchingOff;
  AISwitchSoundEffects soundEffects;
  AISwitchStateActions stateActions;
  bool autoReset;
  int32 numTimesUseOn;
  int32 numTimesUseOff;
  bool switchedOn;
  SWITCHSTATE switchState;
  AISwitchQuicksave2 aiSwitchQuicksave2;
  AISwitchQuicksave aiSwitchQuicksave;
};

struct AIAmmoBundle : ModelDetailDynamic {
  bool active;
  ResourceRef ammoPickupType;
  float respawnTime;
  AIAmmoBundleAIAmmoBundleQuicksave aiAmmoBundleAIAmmoBundleQuicksave;
  AIAmmoBundleAIAmmoBundleQuicksave quicksave;
};

struct AIPickupItemHealth : WorldObjectModel {
  bool reActivateTime;
  bool active;
  float timeHidden;
  bool neverHide;
  bool onceOnly;
  float pickupRadius;
  PICKUP type;
  AIPickupItemHealthQuicksave aiPickupItemHealthQuicksave;
};

struct AIElectricFencePost : ModelDetailDynamic {
  bool on;
  uint32 health;
  bool vulnerability;
  AIElectricFencePostQuicsave aiElectricFencePostQuicsave;
  AIElectricFencePostQuicsave quicksave;
};

struct AIElectricFence : WorldObject {
  ResourceRef post0;
  ResourceRef post1;
  bool active;
  AIElectricFenceQuicksave aiElectricFenceQuicksave;
};

struct AIDoorSoundEffects {
  ResourceRef unlock;
  ResourceRef lock;
  ResourceRef open;
  ResourceRef close;
  ResourceRef inMotionLooping;
  ResourceRef endMotion;
  void ReflectorTag();
};

struct AIDoorStateActions {
  ResourceRef closed;
  ResourceRef opening;
  ResourceRef opened;
  ResourceRef closing;
  void ReflectorTag();
};

struct AIDoor : WorldObjectModel {
  ResourceRef animOpening;
  ResourceRef animClosing;
  bool autoOpen;
  bool autoClose;
  bool allowInterrupting;
  float autoOpenRadius;
  float autoCloseRadius;
  AITYPEID autoAIType;
  AIDoorSoundEffects soundEffects;
  AIDoorStateActions stateActions;
  ResourceRef portal0;
  ResourceRef portal1;
  bool switchedOn;
  DOORSTATE doorState;
  AIDoorQuicksave2 aiDoorQuicksave;
  AIDoorQuicksave quicksave;
};

struct AIPickupItemObjective : AIPickupItemHealth {
  std::string message;
};

struct AIAmmoBox : WorldObjectModel {
  bool active;
  int32 totalAmmo;
  AIAmmoBundleAIAmmoBundleQuicksave aiAmmoBoxQuicksave;
  AIAmmoBundleAIAmmoBundleQuicksave quicksave;
};
