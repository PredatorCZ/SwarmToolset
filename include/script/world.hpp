#pragma once
#include "quicksave/world.hpp"
#include "world_base.hpp"
#include <map>

struct WorldObjectContextShadowVolume {
  bool useStaticVolume;
  float extrusionDepth;
  void ReflectorTag();
};

struct WorldObjectContextContextSplitting {
  bool allowSplitting;
  float maxTreeDepth;
  void ReflectorTag();
};

enum class EnvironmentalFX {
  None,
  Plain,
  PaddedCell,
  Room,
  Bathroom,
  LivingRoom,
  StoneRoom,
  Auditorium,
  ConcertHall,
  Cave,
  Arena,
  Hangar,
  Hallway,
  StoneCorridor,
  Alley,
  Forest,
  City,
  Mountains,
  Quarry,
  Generic,
  SewerPipe,
  Underwater,
  Drugged,
  Dizzy,
  Psychotic,
  Unused,
};

struct WorldObjectContext : WorldObject {
  AABB aabb;
  uint32 flags;
  WorldObjectContextShadowVolume shadowVolume;
  bool terrainShadow;
  WorldObjectContextContextSplitting contextSplitting;
  bool inheritLights;
  bool transition;
  std::vector<std::string> allLights;
  EnvironmentalFX environmentalFX;
  ResourceRef audioFXResource;
  float eaxVolume;
};

enum LIGHT {
  LIGHT_DIRECTIONAL,
  LIGHT_POINT,
  LIGHT_SPOT,
};

enum class LightInfluence {
  Terrain,
  Models,
  Both,
};

enum class LightPriority {
  Lowest,
  Low,
  Normal,
  High,
  Highest,
};

struct WorldObjectLightContextOverride {
  std::string key;
  bool value;
  void ReflectorTag();
  void ReflectorMap();
};

struct WorldObjectLight : WorldObject {
  LIGHT type;
  bool createsShadows;
  Color ambient;
  Color diffuse;
  Color specular;
  float range;
  float angle;
  float aspectRatio;
  float multiplier;
  Vector position;
  Vector direction;
  Vector localX;
  bool on;
  LightPriority priority;
  LightInfluence influence;
  bool dynamic;
  float attenuation;
  AFileInfo spotTexture;
  float spotOffset;
  ResourceArray modifiers;
  std::vector<WorldObjectLightContextOverride> contextOverrides;
};

struct WorldObjectUsableAABB : WorldObject {
  AABB aabb;
  ResourceRef targetObject;
  ResourceRef usePrompt;
  bool cannotUsePrompt;
  bool activeArea;
  ResourceRef invItem;
  WorldObjectUsableAABBQuicksave worldObjectUsableAABBQuicksave;
};

struct WorldMatrix : es::Matrix44 {
  void ReflectorTag();
};

struct ModelTerrain : WorldObjectModel {
  WorldMatrix worldMatrix;
};

struct WorldObjectPortalVertices {
  Vector v0;
  Vector v1;
  Vector v2;
  Vector v3;
  void ReflectorTag();
};

struct WorldObjectPortal : ResourcePack {
  bool active;
  WorldObjectPortalVertices portalVertices;
  ResourceRef observerContextRef;
  ResourceRef destinationContextRef;
  ResourceRef propagateVisibility;
  ResourceRef adjoiningPortal;
};

struct ModelAnimated : ModelDetailDynamic {
  float animationSpeed;
  bool looping;
  ResourceRef animation;
  bool playSound;
  ResourceRef sound;
  ResourceArray soundList;
  bool soundBone;
  bool loopOnAnim;
  bool materialEffects;
  ModelAnimatedQuicksave modelAnimatedQuicksave;
  ResourceArray switchTriggers;
  ModelAnimatedQuicksave2 quicksave;
};

struct AtmosphericsWindCurrent {
  Vector direction;
  float height;
  float turbulence;
  float changePeriod;
  float maximumTurbulenceChange;
  void ReflectorTag();
};

struct AtmosphericsWind {
  Vector direction;
  float currentBlockSize;
  AtmosphericsWindCurrent current01;
  AtmosphericsWindCurrent current02;
  AtmosphericsWindCurrent current03;
  void ReflectorTag();
};

struct AtmosphericsSoftShadows {
  uint32 blurIterations;
  float centerWeight;
  float sideWeight;
  float texelOffset;
  void ReflectorTag();
};

struct Atmospherics : Resource {
  Color RayleighColour;
  Color MieColour;
  float MieFactor;
  float FogHalfDistance;
  float FogPercentMie;
  float InScatteringModifier;
  AtmosphericsWind wind;
  ResourceRef sunLight;
  AtmosphericsSoftShadows softShadows;
  Color indoorAmbient;
  Color indoorDiffuse;
  Color indoorSpecular;
  float viewingDistance;
};

struct ModelDestructable : ModelDetailDynamic {
  ResourceRef destructableObjectResource;
  ResourceRef bonusAmmoPickupResource;
  uint32 bonusAmmoNum;
  uint32 health;
};

struct WorldObjectDecal : WorldObject {
  ResourceRef resource;
  bool permanent;
  Vector centre;
  Vector normal;
  float radius;
};

struct LightModifierAnimate : ResourcePack {
  bool active;
  ResourceRef modelObject;
  std::string boneName;
  bool affectPosition;
  bool affectOrientation;
  LightModifierAnimateQuicksave lightModifierAnimateQuicksave;
};

struct LightModifierFlicker : ResourcePack {
  bool active;
  float intensity1;
  float intensity2;
  float duration1;
  float duration2;
  float transitionPeriod;
  bool randomize;
  float durationJitter;
  float intensityJitter;
  LightModifierFlickerQuicksave lightModifierFlickerQuicksave;
};

struct ContextModifier : ResourcePack {
  bool active;
  ResourceRef context;
  float targetValue;
  float transitionPeriod;
  ContextModifierQuicksave contextModifierQuicksave;
};

struct WorldObjectContainer : Resource {
  ResourceArray groupMembers;
};

struct LightModifierSetColor : ResourcePack {
  bool active;
  Color ambient;
  Color diffuse;
  Color specular;
  bool transitionPeriod;
  LightModifierSetColorQuicksave lightModifierSetColorQuicksave;
};

struct CompiledTerrain : ResourcePack {};
