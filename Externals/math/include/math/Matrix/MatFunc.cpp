#include "MatFunc.h"

using namespace Math::Matrix::Func;
using namespace Math::Matrix;

Mat3x4 Math::Matrix::Func::Identity3x4() {
  return {{
      {1, 0, 0, 0}, // X軸
      {0, 1, 0, 0}, // Y軸
      {0, 0, 1, 0}  // Z軸
  }};
}

