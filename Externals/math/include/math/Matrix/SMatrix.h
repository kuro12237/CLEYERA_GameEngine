#pragma once

namespace Math::Matrix {

struct Mat3x4 {

  float m[3][4];

  /// <summary>
  /// 単位行列
  /// </summary>
  void Identity();

  void Update();

};

} // namespace Math::Matrix