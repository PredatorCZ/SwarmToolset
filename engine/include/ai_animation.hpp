#pragma once
#include "animation.hpp"
#include "resource_ptr.hpp"
#include <list>

struct ResourceObjectAnimation;
struct ResourceSound;

struct AIAnimation : Animation {
  std::list<ResourcePtr<ResourceSound>> *soundList;
  float soundPropability;
  int soundNode;
  int field_60;
  ResourceObjectAnimation *resource;
};
