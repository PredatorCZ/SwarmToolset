#pragma once
#include "core.hpp"
#include "enum_share.hpp"

struct ResourceParticleTypeSimple : ResourcePack {
  AFileInfo texture;
  Color emissive;
  BLEND srcBlend;
  BLEND destBlend;
  Color ambient;
  Color diffuse;
};

struct ResourceParticleExplosionFlame {
  Color startColour;
  Color endColour;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float startSize;
  float endSize;
  float life;
  void ReflectorTag();
};

struct ResourceParticleExplosionSmoke {
  float minU;
  float maxU;
  float minV;
  float maxV;
  float startSize;
  float endSize;
  float life;
  void ReflectorTag();
};

struct ResourceParticleExplosion : ResourcePack {
  ResourceRef flameParticleType;
  ResourceRef smokeParticleType;
  ResourceRef soundEffect;
  ResourceParticleExplosionFlame flame;
  ResourceParticleExplosionSmoke smoke;
  float dontDrawProcessDist;
};

struct ResourceParticleAnimatedOABB : ResourcePack {
  ResourceRef particleType;
  float minU;
  float minV;
  float maxU;
  float maxV;
  Color startColour;
  Color endColour;
  float startSize;
  float endSize;
  float rate;
  float random;
  float life;
  float gravity;
  float drag;
  float fireDamageFactor;
  float dontDrawProcessDist;
};

struct ResourceParticleBlastCloudDebris {
  ResourceRef particleType;
  Color colour;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float size;
  void ReflectorTag();
};

struct ResourceParticleBlastCloudData : ResourceParticleBlastCloudDebris {
  uint32 num;
};

struct ResourceParticleBlastCloud : ResourcePack {
  ResourceParticleBlastCloudDebris debris;
  ResourceParticleBlastCloudDebris fingers;
  ResourceParticleBlastCloudData cloud;
};

enum class RenderTarget {
  SCREEN,
  GLOW,
  DISTORT,
};

struct TexCoord {
  float minU;
  float maxU;
  float minV;
  float maxV;
  void ReflectorTag();
};

struct TexCoord2 : TexCoord {
  void ReflectorTag();
};

struct ResourceParticleDust : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  Color colour;
  TexCoord2 texCoord;
  float startSize;
  float endSize;
  float lifeTime;
  float gravity;
  float drag;
  Vector wind;
  float diffusion;
  float lodFactor;
  float dontDrawProcessDist;
};

struct ResourceParticleDustEx : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  Color colour;
  TexCoord2 texCoord;
  float startSize;
  float endSize;
  float lifeTime;
  float gravity;
  float gravityAlongNormal;
  float drag;
  float diffusion;
  float endDiffusion;
  float kickupRate;
  Vector kickupVelocity;
  float kickupVariance;
  float moving;
  float notMovingLife;
  float startPopulatedPcent;
  float lockToBoneTime;
  Vector force1;
  Vector force2;
  Vector force3;
  Vector force4;
};

struct ResourceParticleDustRingParticle {
  ResourceRef particleType;
  float minU;
  float minV;
  float maxU;
  float maxV;
  Color colour;
  float size;
  float life;
  void ReflectorTag();
};

struct ResourceParticleDustRingLaunch {
  float rate;
  float velUp;
  float velOut;
  void ReflectorTag();
};

struct ResourceParticleDustRing : ResourcePack {
  ResourceParticleDustRingParticle particle;
  ResourceParticleDustRingLaunch launch;
};

struct ResourceParticleElectricFence : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  TexCoord texCoord;
  float length;
  float size;
  float speed;
  float sparksPerSec;
  float startRandomizer;
  float endRandomizer;
  float arcsPerSpark;
  float sectionsPerArc;
  float sectionsVariance;
  float arcLife;
  float textureAlignAtPostPcent;
  float textureAlignAtEndPcent;
  float uvRandomSpeed;
  float posRandomSpeed;
  float lightRangePost;
  float lightRangeEffect;
};

struct ResourceParticleSmokeTrail : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  TexCoord texCoord;
  Color startColour;
  Color endColour;
  float startSize;
  float endSize;
  float rate;
  float life;
  float drag;
  float gravity;
  float random;
  float constantRotation;
  float randomRotation;
  float fadeUpTime;
};

struct ResourceParticleGenericTextureInfo {
  float minU;
  float minV;
  float maxU;
  float maxV;
  bool randomFlipX;
  bool randomFlipY;
  Color colorStart;
  Color colorEnd;
  void ReflectorTag();
};

struct ResourceParticleGenericLaunchInfo {
  float launchNum;
  float sizeStart;
  float sizeEnd;
  float velNormalMin;
  float velNormalMax;
  float velSpreadMin;
  float velSpreadMax;
  void ReflectorTag();
};

struct ResourceParticleGenericMovementInfo {
  float gravity;
  float drag;
  float lifeMin;
  float lifeMax;
  void ReflectorTag();
};

struct ResourceParticleGenericScalingInfo {
  float scaleNumber;
  float scaleSize;
  float scaleLife;
  float scaleVel;
  void ReflectorTag();
};

struct ResourceParticleGenericTrailInfo {
  bool active;
  bool particle2DActive;
  uint32 numBounces;
  float lenScale;
  float widScale;
  float velScale;
  float sizeTimeScale;
  Color trailColourStart;
  Color trailColourEnd;
  float trailMin_u;
  float trailMin_v;
  float trailMax_u;
  float trailMax_v;
  bool trailRandomFlipX;
  bool trailRandomFlipY;
  void ReflectorTag();
};

struct ResourceParticleGeneric : ResourcePack {
  ResourceRef particleType;
  ResourceRef trailParticleType;
  RenderTarget renderTarget;
  float effectLifeTime;
  float startDelay;
  ResourceParticleGenericTextureInfo textureInfo;
  ResourceParticleGenericLaunchInfo launchInfo;
  ResourceParticleGenericMovementInfo movementInfo;
  ResourceParticleGenericScalingInfo scalingInfo;
  ResourceParticleGenericTrailInfo trailInfo;

  float decalChance;
  float dontDrawProcessDist;
  ResourceArray resourceDecals;
};

struct ResourceParticleFireflySprayLiquid {
  ResourceRef particleType;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float launchRate;
  float launchVel;
  float launchRand;
  float life;
  float gravity;
  float drag;
  float startSize;
  float endSize;
  Color startColour;
  Color endColour;
  void ReflectorTag();
};

struct ResourceParticleFireflySprayFlame {
  ResourceRef particleType;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float launchRate;
  float life;
  float gravity;
  float drag;
  float startSize;
  float endSize;
  Color startColour;
  Color endColour;
  void ReflectorTag();
};

struct ResourceParticleFireflySprayFloor {
  float timeFactor;
  float spread;
  void ReflectorTag();
};

struct ResourceParticleFireflySprayDamage {
  float damageDelay;
  float strengthBlast;
  float strengthHeat;
  float strengthCorrosive;
  float hotspot;
  float falloff;
  void ReflectorTag();
};

struct ResourceParticleFireflySprayDistortion {
  float distortionOn;
  Color distortionStartColour;
  float distortionLifeScale;
  float distortionSizeScale;
  float distortionKickupPcent;
  void ReflectorTag();
};

struct ResourceParticleFireflySpray : ResourcePack {
  ResourceParticleFireflySprayLiquid liquid;
  ResourceParticleFireflySprayFlame flame;
  ResourceParticleFireflySprayFloor floor;
  ResourceParticleFireflySprayDamage damage;
  ResourceParticleFireflySprayDistortion distortion;
};

struct ResourceParticleNuclearBlastControl : ResourcePack {
  float autoPopulateTime;
  float fadeupStartTime;
  float fadeupEndTime;
  float slowStartTime;
  float slowEndTime;
  float slowMinScale;
  AABB kickupAABB;
};

struct ResourceParticleNuclearBlastProcess {
  Color color;
  float size;
  float pos0to1;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastKickupTypeDustEx {
  bool active;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastKickupTypesGeneric {
  bool active;
  bool applyBoneMatToNormal;
  Vector normal;
  float velNormMin;
  float velNormMax;
  float velSpreadMin;
  float velSpeadMax;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastKickupTypes {
  ResourceParticleNuclearBlastKickupTypeDustEx dustEx;
  ResourceParticleNuclearBlastKickupTypesGeneric generic;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastForce {
  float startTime;
  float endTime;
  float startVel;
  float endVel;
  float withDir;
  float againstDir;
  float dirX;
  float dirY;
  float dirZ;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastRotation {
  float rotStartSpeed;
  float rotFinalSpeed;
  float rotFinalTime;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastAnimation {
  float on;
  float numWid;
  float numHgt;
  float time;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastDamage {
  float delay;
  float strengthSonic;
  float blastHotspot;
  float blastFalloff;
  void ReflectorTag();
};

struct ResourceParticleNuclearBlastAttack : ResourceParticleNuclearBlastProcess{};
struct ResourceParticleNuclearBlastDecay : ResourceParticleNuclearBlastProcess{};
struct ResourceParticleNuclearBlastSustain : ResourceParticleNuclearBlastProcess{};
struct ResourceParticleNuclearBlastRelease : ResourceParticleNuclearBlastProcess{};
struct ResourceParticleNuclearBlastFinal : ResourceParticleNuclearBlastProcess{};

struct ResourceParticleNuclearBlast : ResourcePack {
  ResourceRef particleType;
  bool active;
  bool renTargetScreen;
  bool renTargetDistort;
  bool renTargetBlur;
  bool renTargetGlow;
  float startDelay;
  bool populateThisPhase;
  bool fadeupThisPhase;
  Vector kickupAABBOffset;
  Vector kickupAABBOffsetInc;
  TexCoord2 texCoord;
  float lifeTime;
  bool processType;
  ResourceParticleNuclearBlastAttack attack;
  ResourceParticleNuclearBlastDecay decay;
  ResourceParticleNuclearBlastSustain sustain;
  ResourceParticleNuclearBlastRelease release;
  ResourceParticleNuclearBlastFinal final;
  float gravity;
  float gravityAlongNormal;
  float drag;
  float diffusion;
  float endDiffusion;
  ResourceParticleNuclearBlastKickupTypes kickupTypes;
  float kickupRate;
  Vector kickupVelocity;//:
  float kickupVelScale;
  float kickupVariance;
  bool moving;
  float notMovingLife;
  float lockToBoneTime;
  ResourceParticleNuclearBlastForce force1;
  ResourceParticleNuclearBlastForce force2;
  ResourceParticleNuclearBlastForce force3;
  ResourceParticleNuclearBlastForce force4;
  ResourceParticleNuclearBlastRotation rotation;
  ResourceParticleNuclearBlastAnimation animation;
  ResourceParticleNuclearBlastDamage damage;
};

struct ResourceParticleNapalm : ResourcePack {
  ResourceRef flameParticleType;
  ResourceRef smokeParticleType;
  ResourceParticleExplosionFlame flame;
  ResourceParticleExplosionSmoke smoke;
};

struct ResourceParticlePlasmaSplashLaunch {
  float number;
  float velUp;
  float velOut;
  float gravity;
  void ReflectorTag();
};

struct ResourceParticlePlasmaSplashParticles {
  ResourceRef particleType;
  float minU;
  float minV;
  float maxU;
  float maxV;
  Color startColour;
  Color endColour;
  float startSize;
  float endSize;
  float minLife;
  float maxLife;
  void ReflectorTag();
};

struct ResourceParticlePlasmaSplashLight {
  Color startColour;
  Color endColour;
  float startSize;
  float endSize;
  float life;
  void ReflectorTag();
};

struct ResourceParticlePlasmaSplashCollision {
  float maxMapSize;
  float minMapSize;
  float maxLODRange;
  void ReflectorTag();
};

struct ResourceParticlePlasmaSplashFlash {
  ResourceRef particleType;
  float minU;
  float minV;
  float maxU;
  float maxV;
  Color startColour;
  Color endColour;
  float startSize;
  float endSize;
  float life;
  void ReflectorTag();
};

struct ResourceParticlePlasmaSplash : ResourcePack {
  ResourceParticlePlasmaSplashLaunch launch;
  ResourceParticlePlasmaSplashParticles particles;
  ResourceParticlePlasmaSplashLight light;
  ResourceParticlePlasmaSplashCollision collision;
  ResourceParticlePlasmaSplashFlash flash;
};

struct ResourceParticleTracerFire : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
  float length;
  float size;
  float speed;
  float numPerSecond;
  Color colour;
};

struct ResourceParticleMoritiaMuzzleFlash : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
  float time;
  float lightRange;
  Color lightAmbient;
  Color lightDiffuse;
  Color lightSpecular;
};

struct ResourceParticleMoritiaMk4HitFlash : ResourcePack {
  ResourceRef particleType;
  TexCoord flashTexCoord;//:
  TexCoord sprayTexCoord;//:
};

struct ResourceParticleMoritiaMk4VentCloudData {
  float rate;
  float life;
  float changeCloudSize;
  float size;
  float velX;
  float velY;
  float velZ;
  float random;
  void ReflectorTag();
};

struct ResourceParticleMoritiaMk4Vent : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  bool drawVentGraphic;
  Color colour;
  TexCoord texCoord;
  float time;
  float size;
  float random;
  TexCoord cloudTexCoord;
  ResourceParticleMoritiaMk4VentCloudData cloudData;
};

struct ResourceParticleSimple3DLight {
  bool on;
  float multiplier;
  float range;
  Color colour;
  Color ambientColour;
  void ReflectorTag();
};

struct ResourceParticleSimple3D : ResourcePack {
  ResourceRef particleType;
  RenderTarget renderTarget;
  float lineWidScale;
  float lineLenScale;
  float uvRandomSpeed;
  bool fadeUsingArc;
  float quadRotZAngInc;
  bool alignToScreen;
  bool alignToScreenAtPos;
  bool oneMatrixForAllQuads;
  Color colour;
  TexCoord2 texCoord;
  float startSize;
  float endSize;
  float lifeTime;
  float gravity;
  float drag;
  Vector wind;
  float diffusion;
  float lodFactor;
  ResourceParticleSimple3DLight light;
};

struct ResourceParticleSystemDescriptor : ResourcePack {
  ResourceRef resourceObjectModel;
  ResourceRef resourceParticleSystem;
  ResourceRef soundFireLoop;
  ResourceRef soundFireStart;
  ResourceRef soundFireEnd;
};

struct ResourceParticleWarriorBulletHit : ResourcePack {
  ResourceRef particleType;
  TexCoord shellPieceTexCoord;
  TexCoord bloodBlobTexCoord;
  TexCoord bloodSprayTexCoord;
};

struct ResourceParticleTankerSprayLiquid {
  ResourceRef particleType;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float launchRate;
  float launchVel;
  float launchRand;
  float life;
  float gravity;
  float drag;
  float startSize;
  float endSize;
  Color startColour;
  Color endColour;
  void ReflectorTag();
};

struct ResourceParticleTankerSprayFlame {
  ResourceRef particleType;
  float minU;
  float maxU;
  float minV;
  float maxV;
  float launchRate;
  float life;
  float gravity;
  float drag;
  float startSize;
  float endSize;
  Color startColour;
  Color endColour;
  void ReflectorTag();
};

struct ResourceParticleTankerSprayFloor {
  float timeFactor;
  float spread;
  void ReflectorTag();
};

struct ResourceParticleTankerSpray : ResourcePack {
  ResourceParticleTankerSprayLiquid liquid;
  ResourceParticleTankerSprayFlame flame;
  ResourceParticleTankerSprayFloor Floor;
};

struct ResourceParticleMuzzleFlash : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
  float time;
  float lightRange;
  Color lightAmbient;
  Color lightDiffuse;
  Color lightSpecular;
  float petalFwdScale;
  float petalFwdScaleVariance;
  float muzzleFlash1Hgt;
  float muzzleFlash1Len;
  float muzzleFlash2Hgt;
  float muzzleFlash2Len;
  float muzzleFlash1Variance;
  float muzzleFlash2Variance;
  float typeAZAdjust1;
  float typeAZAdjust2;
  float typeBZAdjust1;
  float typeBZAdjust2;
  float size;
  uint32 numAnims;
  bool startAnimIfDelayed;
  float startAnimDelayTime;
};

struct ResourceParticleConTrail : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
  Color startColour;
  Color endColour;
  float rate;
  float life;
  float startWidth;
  float endWidth;
  float gravity;
  float random;
  float minVisibleSpeed;
  float maxVisibleSpeed;
};

struct ResourceParticleLights : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
  float time;
  float lightRange;
  Color lightAmbient;
  Color lightDiffuse;
  Color lightSpecular;
  float petalFwdScale;
  float petalFwdScaleVariance;
  float muzzleFlash1Hgt;
  float muzzleFlash1Len;
  float muzzleFlash2Hgt;
  float muzzleFlash2Len;
  float muzzleFlash1Variance;
  float muzzleFlash2Variance;
  float typeAZAdjust1;
  float typeAZAdjust2;
  float typeBZAdjust1;
  float typeBZAdjust2;
  float size;
  uint32 numAnims;
  float startAnimIfDelayed;
  float startAnimDelayTime;
  uint32 numSpokes;
  float startAngle;
  float spokeLen;
  float spokeWidBase;
  float spokeWidEnd;
  Color spokeColour;
};

struct ResourceParticleBulletHitDebrisTextureInfo {
  float minU;
  float minV;
  float maxU;
  float maxV;
  Color colorStart;
  Color colorEnd;
  void ReflectorTag();
};

struct ResourceParticleBulletHitDebrisLaunchInfo {
  uint32 launchNum;
  float size_Start;
  float sizeEnd;
  float minLife;
  float maxLife;
  float launchVel;
  float velVariance;
  float gravity;
  void ReflectorTag();
};

struct ResourceParticleBulletHitDebris : ResourcePack {
  ResourceRef particleType;
  ResourceParticleBulletHitDebrisTextureInfo textureInfo;
  ResourceParticleBulletHitDebrisLaunchInfo launchInfo;
};

struct ResourceParticleBulletHitDust : ResourcePack {
  ResourceRef particleType;
  TexCoord texCoord;
};

struct ResourceParticleBlood : ResourcePack {
  ResourceRef particleType;
  TexCoord bloodBlobTexCoord;
  TexCoord bloodSprayTexCoord;
};

struct ResourceParticleFlareParticle {
  ResourceRef particleType;
  float Min_U;
  float Max_U;
  float Min_V;
  float Max_V;
  float Size0;
  float Size1;
  float Life;
  float Rate;
  void ReflectorTag();
};

struct ResourceParticleFlareLight {
  float lightPos;
  float lightRangeMin;
  float lightRangeMax;
  float lightMultiplier;
  bool lightShadow;
  Color lightAmbient;
  Color lightDiffuse;
  Color lightSpecular;
  void ReflectorTag();
};

struct ResourceParticleFlare : ResourcePack {
  ResourceParticleFlareParticle flare;
  ResourceParticleFlareParticle smoke;
  float burnTime0;
  float burnTime1;
  float burnTime2;
  float burnTime3;
  ResourceParticleFlareLight light;
};

struct ResourceParticleBloodSpurtParticle {
  Color colour;
  float launchNum;
  float startSize;
  float endSize;
  float life;
  float launchVel;
  float random;
  float gravity;
  void ReflectorTag();
};

struct ResourceParticleBloodSpurt : ResourcePack {
  ResourceRef particleType;
  TexCoord textureInfo;
  ResourceParticleBloodSpurtParticle spurt;
  ResourceParticleBloodSpurtParticle spray;
};

struct ResourceParticleDustStormRain {
  bool rainActive;
  Vector rainVel;
  Vector rainKickupSize;
  uint32 launchNum;
  float rainLife;
  float launchYOffset;
  float lenScale;
  float widScale;
  float velScale;
  Color colourStart;
  Color colourEnd;
  float rainMinU;
  float rainMinV;
  float rainMaxU;
  float rainMaxV;
  void ReflectorTag();
};

struct ResourceParticleDustStorm : ResourcePack {
  ResourceRef particleType;
  Color colour;
  TexCoord2 texCoord;
  float startSize;
  float endSize;
  float lifeTime;
  float gravity;
  float drag;
  Vector wind;
  float kickupRate;
  float kickupVariance;
  Vector kickupVelocity;
  float diffusion;
  float grapFromAtmosphere;
  Color rayLeighColour;
  Color mieColour;
  float mieFactor;
  float fogHalfDistance;
  float fogPercentMie;
  float inScatteringModifier;
  float changeTime;
  bool useAtmosphereSettings;
  bool aroundCamera;
  ResourceParticleDustStormRain rainData;
};
