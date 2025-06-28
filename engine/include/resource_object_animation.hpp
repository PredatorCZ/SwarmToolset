#pragma once
#include "ai_animation.hpp"
#include "resource_object.hpp"
#include "resource_ptr.hpp"
#include "serializable.hpp"

struct RenderState;
struct ResourceObjectModel;
struct ResourceObjectAnimationSet;

struct ResourceObjectAnimation : ResourceObject, Serializable {
  void SampleToRenState(RenderState *state, float unk);

  float duration;
  float field_60;
  std::string fileName;
  AIAnimation animation;
  ResourceObjectModel *refModel;
  ResourceObjectAnimationSet *animationSet;
  float soundProbability;
  ResourcePtr<ResourceObject> sound_sl;
  std::list<void *> soundList;
  int soundBone;
  int field_160;
  int field_164;
  std::string boneNameExtension;
  float scaleTolerance;
  float rotateTolerance;
  float positionTolerance;
};
