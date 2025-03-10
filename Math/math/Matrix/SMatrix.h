#pragma once
#include<cassert>

namespace Math::Matrix {

/// <summary>
/// 4x4行列
/// </summary>
struct Mat4x4 {

  float m[4][4];

  /// <summary>
  /// 単位行列
  /// </summary>
  void Identity();

  /// <summary>
  /// 逆行列
  /// </summary>
  Mat4x4 Inverse();

};

/// <summary>
/// 3x4行列
/// </summary>
struct Mat3x4 {

  float m[3][4];

  /// <summary>
  /// 単位行列
  /// </summary>
  void Identity();


  /// <summary>
  /// 4x4からの変換
  /// </summary>
  void FromMat4x4(const Mat4x4 &mat);


};

} // namespace Math::Matrix