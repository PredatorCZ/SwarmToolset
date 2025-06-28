#include "matrix_access.hpp"
#include "dx_types.hpp"
#include <cstring>

void MatrixAccess::Set(const Matrix &a2) {
  memcpy(Get(), &a2, sizeof(Matrix));
  field_C();
  needsUpdate = true;
}

void MatrixAccess::SetTransform(const Vector &a2) {
  InsertRow(*Get(), 3, a2);
  needsUpdate = true;
  field_C();
}

const Vector &MatrixAccess::GetTransform() {
  if (needsUpdate) {
    position = Get()->m[3];
    needsUpdate = false;
  }
  return position;
}
