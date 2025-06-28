#pragma once
#include "matrix_access.hpp"
#include "world_object.hpp"

struct WorldObjectMatrix : WorldObject, MatrixAccess {
  void field_50() override;

  Vector *GetPosition() override;
  void SetPosition(Vector *pos) override;

  void field_C() override;

  bool _95AE20(Matrix &argOut, float arg4, float a4, const Matrix &a5);
  bool _95B8E0(Matrix &argOut, const Matrix &arg4, float a4);
};
