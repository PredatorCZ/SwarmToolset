#pragma once
#include "world_base.hpp"

enum class SoundType {
  SpecialFX,
  Music,
  Speech,
};

struct ResourceSound3DParameters {
  float minDistance;
  float maxDistance;
  bool cullByDistance;
  void ReflectorTag();
};

struct ResourceSound : ResourcePack {
  AFileInfo filename;
  SoundType type;
  bool streaming;
  bool positional3D;
  bool stereo;
  bool oggVorbis;
  float limit;
  float priority;
  ResourceSound3DParameters default3DParameters;
  float semitoneShift;
  float random;
  float frontEndSound;
  float startDelay;
  float defaultVolume;
};

struct ResourceSoundRandomised : ResourcePack {
  float limit;
  ResourceArray sounds;
};

struct AudioTweaks : ResourcePack {
  float rolloff;
  float distanceFactor;
  float dopplerFactor;
  float volumeScalingNonPositional;
  float musicVolume;
  float cullDistance;
  float prioritySoundScalingFactor;
};

struct AmbientSoundObject : WorldObject {
  ResourceRef playSound;
  bool startImmediately;
  Vector position;
  bool loopDelayLength;
  bool atmospheric;
};
