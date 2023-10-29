#pragma once
#include "script/core.hpp"

struct WorldObjectUsableAABBQuicksave {
  bool canBeUsed;
  void ReflectorTag();
};

struct ModelAnimatedQuicksave {
  float fAnimationTime;
  void ReflectorTag();
};

struct ModelAnimatedQuicksave2 {
  float fAnimationTime;
  bool getIsActive;
  void ReflectorTag();
};

struct LightModifierAnimateQuicksave {
  Vector originalPosition;
  Vector originalDirection;
  Vector originalLocalX;
  void ReflectorTag();
};

struct LightModifierFlickerQuicksave {
  Color originalAmbient;
  Color originalDiffuse;
  Color originalSpecular;
  float startTime;
  float effectiveIntensity[2];
  float effectiveDuration[2];
  uint32 activeStage;
  void ReflectorTag();
};

struct ContextModifierQuicksave {
  float startValue;
  float startTime;
  void ReflectorTag();
};

struct LightModifierSetColorQuicksave {
  Color originalAmbient;
  Color originalDiffuse;
  Color originalSpecular;
  float startTime;
  void ReflectorTag();
};
