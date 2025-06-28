#pragma once

#include "dx_types.hpp"

struct MatrixAccess {
  // virtual *delete;
  virtual const Matrix *Get() const = 0;
  virtual Matrix *Get() = 0;
  virtual void field_C() = 0;

  void Set(const Matrix &matrix);
  void SetTransform(const Vector &transform);
  const Vector &GetTransform();

  bool needsUpdate;
  Vector position;
};
