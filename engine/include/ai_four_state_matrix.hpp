#pragma once
#include "dx_types.hpp"
#include "sl_variable.hpp"
#include "sl_variable_template.hpp"

struct AIEntity;
struct SLVariableSetMatrix;
struct SLVariable;
struct WorldObject;
struct WorldObjectModel;

struct AIFourStateMatrix {
  AIEntity *ownerEntity;
  double aiTime[4]{-1, -1, -1, -1};
  Matrix aiMatrix[4];
  bool aiMoving[4];
  char unused[272];
  SLVariableTemplate<float> *sl_aiTime[4];
  SLVariableSetMatrix *sl_aiMatrix[4];
  SLVariable *sl_aiMoving[4];

  void SetMatrix(int index, const double &time, const Matrix &matrix,
                 const bool &isMoving);
  void CopyUpperHalfToLower();
  Matrix GetMatrixAtTime(const double &time);
  void Process();
  void _462780();
  void _462CC0(WorldObject &obj, float unk);
  void _462EA0(WorldObjectModel &obj);
};
