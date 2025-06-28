#pragma once
#include <cstdint>
#include <map>
#include <vector>

struct Skeleton;
struct AnimationTrack;
struct Bones;
struct RenderState;

struct SkeletalAnimation {
  void _5C34F0(float unk);
  void _5C5C70(Skeleton *skel);
  void InterpolateToRenderState(RenderState *state, float animTime);
  void _5C50D0(RenderState *state, float a3, float a4, bool unk);
  void _5C4FC0(RenderState *state, float a3, float a4, bool unk);

  uint32_t durationTicks;
  float timeRatio;
  Skeleton *skeleton;
  std::vector<AnimationTrack*> tracks;
  std::map<Skeleton *, Bones *> skeletonBones;
};
