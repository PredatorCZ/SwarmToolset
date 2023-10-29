#pragma once
#include "script/core.hpp"

struct ParticleSystemGenericQuicksave {
  bool getIsActive;
  float kickupRate;
  float nextOffTime;
  float nextOnTime;
  bool initialAutoStart;
  void ReflectorTag();
};

struct ParticleSystemDustStormQuicksave {
  ResourceRef lastResourceGuid;
  Vector lastPosition;
  bool first;
  bool bAutoDelete;
  float timeActive;
  float startTime;
  float lastT;
  bool interpolatingAtmosphere;
  float interpolatingDuration;
  float interpolatingStartTime;
  float interpolatingEndTime;
  Color currentColour;
  Color oldRayleighColour;
  float oldRayleighDensity;
  Color oldMieColour;
  float oldMieFactor;
  float oldMieDensity;
  float oldInScatteringModifier;
  uint32 oldRainLaunchNum;
  bool savedOrigAtmosphereVals;
  Color origRayleighColour;
  float origRayleighDensity;
  Color origMieColour;
  float origMieFactor;
  float origMieDensity;
  float origInScatteringModifier;
  bool particleEffectOn;
  bool particleRainEffectOn;
  uint32 interpolatingRainLaunchNum;
  bool noProcess;
  bool noGetParticles;
  bool forceWindDir;
  bool showDebug;
  float reflectRadius;
  bool flipThruWindDir;
  bool flipThruFwdDir;
  bool ignoreWind;
  bool onlyGetInReflectRadius;
  bool UOORPorig;
  bool isStormActive;
  bool changeAtmosphereStart;
  void ReflectorTag();
};

struct ParticleSystemDustQuicksave {
  float startTime;
  float lastT;
  void ReflectorTag();
};

struct ParticleSystemNuclearBlastQuicksave {
  ResourceRef rpParticleResourceControl;
  ResourceRef rpParticleResource1;
  ResourceRef rpParticleResource2;
  ResourceRef rpParticleResource3;
  ResourceRef rpParticleResource4;
  ResourceRef rpParticleResource5;
  ResourceRef rpParticleResource6;
  ResourceRef rpParticleResource7;
  ResourceRef rpParticleResource8;
  ResourceRef rpParticleResource9;
  ResourceRef rpParticleResource10;
  Vector posLocal;
  bool usePosInsteadOfKickupCenter;
  float timeIntoEffect;
  bool bActive;
  bool bUseKillPlane;
  Vector killPlaneNormal;
  Vector collisionPos;
  void ReflectorTag();
};

struct ParticleSystemAnimatedOABBQuicksave {
  Vector launchBoxMin;
  Vector launchBoxMax;
  float fDamageTime;
  uint32 eType;
  bool bModelRefValid;
  float scaleRate;
  float scaleSize;
  void ReflectorTag();
};

struct ParticleSystemExplosionQuicksave {
  bool getIsActive;
  ResourceRef rpParticleResource;
  float startTime;
  float endTime;
  Vector pos;
  float size;
  bool bFlipX;
  bool bFlipY;
  void ReflectorTag();
};
