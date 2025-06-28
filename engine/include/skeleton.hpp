#pragma once
#include "dx_types.hpp"
#include <vector>

struct Bone;

struct Skeleton {
  void SetTransforms(Matrix &rootTransform, std::vector<Matrix> &transforms);

  Bone *rootBone;
};
