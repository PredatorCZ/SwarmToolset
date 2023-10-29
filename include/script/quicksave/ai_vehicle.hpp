#pragma once
#include "script/core.hpp"

enum AIFVSM {
  AIFVSM_NONE,
  AIFVSM_OLDLANDING,
  AIFVSM_OLDLANDED,
  AIFVSM_OLDTAKEOFF,
  AIFVSM_OLDFLYTOHOVER,
  AIFVSM_OLDHOVER,
  AIFVSM_OLDHOVERTOLAND,
  AIFVSM_DECEL,
  AIFVSM_DESCEND,
  AIFVSM_LOITER,
  AIFVSM_LOITERMOVE,
  AIFVSM_ASCEND,
  AIFVSM_ACCEL,
};

struct AIFlyingVehicleQuicksave {
  AIFlyerTwoStateMatrix aiFlyerTwoStateMatrix;
  float desSpeed;
  AIFVSM fvSpecialMode;
  AIFVSM nextFVSpecialMode;
  ResourceRef pDustRing;
  void ReflectorTag();
};

struct AIBomberQuicksave {
  ResourceRef pConTrail[2];
  void ReflectorTag();
};

struct AIDropshipMarauderQuicksave {
  ResourceRef pConTrail[4];
  bool bDisembarking;
  Vector marauderPos;
  Vector marauderAng;
  void ReflectorTag();
};

struct AIDropshipGruntQuicksave {
  ResourceRef pConTrail[4];
  void ReflectorTag();
};
