#include "quicksave/particle.hpp"

struct ParticleSystemGeneric : ResourcePack {
  ResourceRef particleResource;
  ResourceRef aoundStart;
  ResourceRef aoundStop;
  bool soundStartLoop;
  bool soundStopLoop;
  bool autoStart;
  float minOnTime;
  float maxOnTime;
  float minOffTime;
  float maxOffTime;
  AABB kickupAABB;
  Vector autoDirection;
  ParticleSystemGenericQuicksave particleSystemGenericQuicksave;
};

struct ParticleSystemDustStorm : ResourcePack {
  ResourceRef particleResource;
  AABB kickupAABB;
  bool active;
  ParticleSystemDustStormQuicksave particleSystemDustStormQuicksave;
};

struct ParticleSystemDust : ResourcePack {
  ResourceRef particleResource;
  AABB kickupAABB;
  float kickupRate;
  Vector kickupVelocity;
  float kickupVariance;
  bool bStartPopulated;
  bool autoDelete;
  bool active;
  float timeActive;
  float startDelay;
  ParticleSystemDustQuicksave particleSystemDustQuicksave;
};

struct ParticleSystemNuclearBlast : ResourcePack {
  bool active;
  ResourceRef particleResourceControl;
  ResourceRef particleResource1;
  ResourceRef particleResource2;
  ResourceRef particleResource3;
  ResourceRef particleResource4;
  ResourceRef particleResource5;
  ResourceRef particleResource6;
  ResourceRef particleResource7;
  ResourceRef particleResource8;
  ResourceRef particleResource9;
  ResourceRef particleResource10;
  ParticleSystemNuclearBlastQuicksave particleSystemNuclearBlastQuicksave;
};

struct ParticleSystemAnimatedOABB : ResourcePack {
  ResourceRef particleResource;
  ResourceRef targetModel;
  float rateFactor;
  float lifeTime;
  bool active;
  ParticleSystemAnimatedOABBQuicksave particleSystemAnimatedOABBQuicksave;
};

struct ParticleSystemExplosion : ResourcePack {
  ParticleSystemExplosionQuicksave particleSystemExplosionQuicksave;
  ResourceRef explosionParticleResource;
  Vector position;
  float size;
  float damageRadius;
  float damageValue;
  bool lightOn;
};

struct ParticleSystemTerrainDust : ParticleSystemDust {
  uint32 numNodes;
  bool desNodeSize;
  Vector kickupArea;
};
