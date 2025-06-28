#pragma once
#include "resource_object.hpp"
#include "resource_ptr.hpp"
#include <vector>

struct ResourceObjectAnimation;
struct ResourceObjectModel;
struct Animation;

struct ResourceObjectAnimationSet : ResourceObject {
  Animation *PickRandomAnimation();

  std::vector<ResourcePtr<ResourceObjectAnimation>> animations;
  int animationTypeClassIndex;
  ResourceObjectModel *refModel;
};
