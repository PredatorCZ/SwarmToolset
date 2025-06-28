#pragma once
#include "dx_types.hpp"
#include <list>

struct SoundGroupElement {
  virtual void AddSource(Vector *position);
  virtual void RemoveSource(std::list<Vector *>::iterator iter);

  std::list<Vector *> sources;
  int field_C;
  float volume;
  float field_14;
};
