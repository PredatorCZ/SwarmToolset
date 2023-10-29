#pragma once
#include "script/core.hpp"

struct WorldObjectQuicksave {
  ResourceRef pContext;
  void ReflectorTag();
};

struct ModelDetailDynamicQuicksave {
  ResourceRef pRagDoll;
  ResourceRef pFlames;
  ResourceRef pSmoke;
  uint32 flameListNum;
  uint32 smokeListNum;
  void ReflectorTag();
};
