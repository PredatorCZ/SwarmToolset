#pragma once
#include "resource_object.hpp"
#include <string>

struct StreamData;
struct AudioPlayable;

struct ResourceSound : ResourceObject {
  virtual AudioPlayable *CreateAudioPlayable();
  virtual void DeleteAudioPlayable(AudioPlayable *);
  virtual void SetDefaultVolume();
  virtual float GetDefaultVolume();
  virtual void SetSemitoneShift();
  virtual float GetSemitoneShift();
  virtual void SetRandom();
  virtual void GetRandom();
  virtual void SetFromEndSound();

  std::string fileName;
  bool positional3D;
  bool streaming;
  bool stereo;
  bool oggVorbis;
  bool cullByDistance;
  bool priority;
  float minDistance;
  float maxDistance;
  float limit;
  int field_88;
  bool random;
  float semitoneShift;
  bool fromEndSound;
  float defaultVolume;
  StreamData *streamData;
  int type;
  double startDelay;
};
