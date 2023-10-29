#pragma once
#include "quicksave/world_base.hpp"

struct WorldObject : ResourcePack {
  ResourceRef lockedContext;
  ResourceRef debugContext;
  WorldObjectQuicksave worldObjectQuicksave;
};

struct WorldObjectModel : WorldObject {
  ResourceRef resourceRef;
  std::vector<std::string> shaderOverrides;
  Vector position;
  Angle angle;
  bool render;
  bool shadowAtlasCaster;
  bool shadowAtlasReceiver;
};

struct ModelDetailDynamic : WorldObjectModel {
  bool active;
  bool beingControlled;
  bool hasBeenControlled;
  bool movable;
  float breakoutForce;
  float density;
  bool flamable;
  bool explosive;
  ModelDetailDynamicQuicksave modelDetailDynamicquicksave;
};
