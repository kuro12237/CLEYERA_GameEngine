#include "SMatrix.h"

void Math::Matrix::Mat3x4::Identity() {
  m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0;
  m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0;
  m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0;
}

void Math::Matrix::Mat3x4::Update() {}