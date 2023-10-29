#pragma once
#include "script/core.hpp"

struct AICameraQuicksave {
  Vector targetOffset;
  void ReflectorTag();
};

struct AIElectricFencePostQuicsave {
  bool getIsActive;
  float animTime[2];
  void ReflectorTag();
};

struct AIElectricFenceQuicksave {
  float checkTime;
  float lastT;
  ResourceRef pElectricFence;
  void ReflectorTag();
};

struct AIDoorQuicksave {
  bool getIsActive;
  float openFactor;
  void ReflectorTag();
};

struct AIDoorQuicksave2 : AIDoorQuicksave {
  ResourceRef pAvoidanceBox;
  Vector posCentre;
  void ReflectorTag();
};

struct AILandMineQuicksave {
  float nextCheckTime;
  float lastWarnTime;
  void ReflectorTag();
};

struct AISwitchQuicksave {
  bool getIsActive;
  float posFactor;
  float lastSwitchTime;
  void ReflectorTag();
};

struct AISwitchQuicksave2 : AISwitchQuicksave {
  float lastSwitchTime;
  void ReflectorTag();
};

struct AIAmmoBundleAIAmmoBundleQuicksave {
  float nextCheckTime;
  void ReflectorTag();
};

struct AIPickupItemHealthQuicksave {
  float nextPickupTime;
  bool bHidden;
  void ReflectorTag();
};
