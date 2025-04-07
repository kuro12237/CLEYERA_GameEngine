#pragma once

#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

namespace system {

struct OBB {

   Math::Vector::Vec3 *center = nullptr;
   Math::Vector::Vec3 *rotate{};

   Math::Vector::Vec3 size{1, 1, 1};

   std::array<Math::Vector::Vec3, 3> orientations{};

   Math::Matrix::Mat4x4 *worldMatrix = nullptr;
   void CalculateOrientations() {
      orientations[0] = {worldMatrix->m[0][0], worldMatrix->m[1][0], worldMatrix->m[2][0]}; // X軸の方向ベクトル
      orientations[1] = {worldMatrix->m[0][1], worldMatrix->m[1][1], worldMatrix->m[2][1]}; // Y軸の方向ベクトル
      orientations[2] = {worldMatrix->m[0][2], worldMatrix->m[1][2], worldMatrix->m[2][2]}; // Z軸の方向ベクトル
   }
};

struct AABB {
   Math::Vector::Vec3 min{-1.0f, -1.0f, -1.0f};
   Math::Vector::Vec3 max{1.0f, 1.0f, 1.0f};
};

} // namespace system
} // namespace Collider
} // namespace Util
} // namespace CLEYERA