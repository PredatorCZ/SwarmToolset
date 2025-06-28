#pragma once
#include "game_object.hpp"

struct ResourceObject : GameObject {
  int numRefs;
  int sizeInMemory;
  char field_50;
  char isLoaded;
  char field_4E;
  int classInfo;

  void DecreaseReference();
  void SafeLoad();
};
