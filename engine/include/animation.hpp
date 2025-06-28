#pragma once
#include "render_state.hpp"
#include <cstdint>
#include <string>
#include <vector>

struct SkeletalAnimation;

struct Matrix3x4 {
  Vector m[4];
};

struct Animation {
  uint32_t GetFrame(float animTime);

  std::vector<std::vector<Matrix3x4> *> frames;
  float frameRate;
  float frameDuration;
  float duration;
  int numBones;
  int field_24;
  int field_28;
  SkeletalAnimation *skeletalAnimation;
  std::string resourceGUID;
  int resourceGUIDHash;
  int globalIndex;
};
