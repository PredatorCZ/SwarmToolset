#pragma once
#include "sound_group_element.hpp"
#include "resource_ptr.hpp"

struct ResourceSound;
struct AIEntity;
struct AudioPlayable3DExtended;

struct AudioPlayable : SoundGroupElement
{
  virtual void field_5C();
  virtual bool field_28();
  float volume;
  int field_20;
  ResourcePtr<ResourceSound> soundResource;
  int field_80;
  int field_84;
  char field_88;
  char field_89;
  int field_8C;
  double field_90;
  char field_98;
  char fromEndSound;
  char field_9A;
  AudioPlayable3DExtended *extended3D;
  AIEntity *entity;
  char field_A4;
  char field_A5;
};
