#pragma once

#include "dx_types.hpp"

struct BinaryBuffer;

struct AABoundingBox {
  virtual bool Load(BinaryBuffer *data);
  virtual void Save();

  const Vector &GetCenter();

  Vector min;
  Vector max;
  bool shouldUpdateCenter = 1;
  Vector center;
};
