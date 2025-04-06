#include "ColliderFunc.h"

bool CLEYERA::Util::Collider::system::Func::OBBCheck(const OBB &obb1, const OBB &obb2) {

   // 分離軸テスト
   for (const auto &axis : obb1.orientations) {
      if (!TestAxis(axis, obb1, obb2)) {
         return false;
      }
   }

   for (const auto &axis : obb2.orientations) {
      if (!TestAxis(axis, obb1, obb2)) {
         return false;
      }
   }

   // OBB1の軸とOBB2の軸に垂直な軸をテスト
   for (const auto &axis : {Math::Vector::Vec3{obb1.orientations[1].x * obb2.orientations[2].x - obb1.orientations[2].x * obb2.orientations[1].x, obb1.orientations[1].y * obb2.orientations[2].y - obb1.orientations[2].y * obb2.orientations[1].y,
                                               obb1.orientations[1].z * obb2.orientations[2].z - obb1.orientations[2].z * obb2.orientations[1].z},
                            Math::Vector::Vec3{obb1.orientations[2].x * obb2.orientations[0].x - obb1.orientations[0].x * obb2.orientations[2].x, obb1.orientations[2].y * obb2.orientations[0].y - obb1.orientations[0].y * obb2.orientations[2].y,
                                               obb1.orientations[2].z * obb2.orientations[0].z - obb1.orientations[0].z * obb2.orientations[2].z},
                            Math::Vector::Vec3{obb1.orientations[0].x * obb2.orientations[1].x - obb1.orientations[1].x * obb2.orientations[0].x, obb1.orientations[0].y * obb2.orientations[1].y - obb1.orientations[1].y * obb2.orientations[0].y,
                                               obb1.orientations[0].z * obb2.orientations[1].z - obb1.orientations[1].z * obb2.orientations[0].z}}) {
      if (!TestAxis(axis, obb1, obb2)) {
         return false;
      }
   }

   return true;
}

bool CLEYERA::Util::Collider::system::Func::TestAxis(const Math::Vector::Vec3 &axis, const OBB &obb1, const OBB &obb2) {

   // OBBの射影を計算
   auto projection1 = OBBProjection(obb1, axis);
   auto projection2 = OBBProjection(obb2, axis);

   // 射影が重なっているかチェック
   return ProjectionOverlap(projection1, projection2);
}

std::pair<float, float> CLEYERA::Util::Collider::system::Func::OBBProjection(const OBB &obb, const Math::Vector::Vec3 &axis) {

   float val = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z); // 正規化
   float newAxis = 0.0f;
   newAxis = newAxis / val;

   // OBB上の頂点を取得
   std::array<Math::Vector::Vec3, 8> vertices{};
   for (int i = 0; i < 8; ++i) {
      Math::Vector::Vec3 sign = {(i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f, (i & 4) ? 1.0f : -1.0f};
      vertices[i] = {obb.center.x + obb.orientations[0].x * sign.x * obb.size.x + obb.orientations[1].x * sign.y * obb.size.y + obb.orientations[2].x * sign.z * obb.size.z,
                     obb.center.y + obb.orientations[0].y * sign.x * obb.size.x + obb.orientations[1].y * sign.y * obb.size.y + obb.orientations[2].y * sign.z * obb.size.z,
                     obb.center.z + obb.orientations[0].z * sign.x * obb.size.x + obb.orientations[1].z * sign.y * obb.size.y + obb.orientations[2].z * sign.z * obb.size.z};
   }

   // 頂点を軸に射影
   std::array<float, 8> projections{};
   for (int i = 0; i < 8; ++i) {
      projections[i] = vertices[i].x * axis.x + vertices[i].y * axis.y + vertices[i].z * axis.z;
   }

   auto minmax = std::minmax_element(projections.begin(), projections.end());
   return std::make_pair(*minmax.first, *minmax.second);
}

bool CLEYERA::Util::Collider::system::Func::ProjectionOverlap(const std::pair<float, float> &projection1, const std::pair<float, float> &projection2) {

   // 射影の重なりをチェック
   return (projection1.first <= projection2.second && projection2.first <= projection1.second);
}
