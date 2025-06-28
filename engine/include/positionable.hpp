#pragma once

#include "aa_bounding_box.hpp"

struct Positionable {
  // virtual delete;
  virtual Vector *GetPosition();
  virtual void SetPosition(Vector *pos);

  AABoundingBox bbox;
};
