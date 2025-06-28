#include "ai_four_state_matrix.hpp"
#include "ai_entity.hpp"
#include "app_game.hpp"

void AIFourStateMatrix::SetMatrix(int index, const double &time,
                                  const Matrix &matrix,
                                  const bool &isMoving) {
  aiTime[index] = time;
  aiMatrix[index] = matrix;
  aiMoving[index] = isMoving;
}

void AIFourStateMatrix::CopyUpperHalfToLower() {
  aiTime[0] = aiTime[2];
  aiTime[1] = aiTime[3];
  aiMatrix[0] = aiMatrix[2];
  aiMatrix[1] = aiMatrix[3];
  aiMoving[0] = aiMoving[2];
  aiMoving[1] = aiMoving[3];
}

Matrix AIFourStateMatrix::GetMatrixAtTime(const double &time) {
  int index = 0;
  double *v4 = &aiTime[1];

  do {
    if (time <= *v4)
      break;
    ++index;
    ++v4;
  } while (index < 3);

  if (index == 3 && time > aiTime[3]) {
    return aiMatrix[3];
  }

  if (aiMatrix[index] != aiMatrix[index + 1]) {
    double v8 = (time - aiTime[index]) / (aiTime[index + 1] - aiTime[index]);
    float v14 = v8 * v8;
    double v9 = v8 * v8 * 3.0 - (v14 * v8 + v14 * v8);

    Matrix p0 = aiMatrix[index] * (1.0 - v9);
    Matrix p1 = aiMatrix[index + 1] * v9;
    Matrix blendMtx = p0 + p1;

    if (aiMoving[index]) {
      if (!aiMoving[index + 1])
        v8 = 1.0 - (1.0 - v8) * (1.0 - v8);
    } else if (aiMoving[index + 1]) {
      v8 = v14;
    } else {
      v8 = v9;
    }

    reinterpret_cast<Vector &>(blendMtx.m[3]) =
        reinterpret_cast<Vector &>(aiMatrix[index].m[3]) * (1.0 - v8) +
        reinterpret_cast<Vector &>(aiMatrix[index + 1].m[3]) * v8;
    // Matrix_694D60(&v41);
    return blendMtx;
  }

  return {};
}

void AIFourStateMatrix::Process() {
  const double sessionTime = AppGame::Get()->SessionTime();
  ownerEntity->Set(GetMatrixAtTime(sessionTime));
}
