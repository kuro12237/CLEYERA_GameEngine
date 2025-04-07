#include "ColliderFunc.h"

void CLEYERA::Util::Collider::system::Func::MakeLinesFromOBB(std::vector<Math::Vector::Vec3> &outLines, const OBB &obb) {
   using Vec3 = Math::Vector::Vec3;

   // 軸方向 × ハーフサイズ
   Vec3 right = obb.orientations[0] * (obb.size.x * 0.5f);
   Vec3 up = obb.orientations[1] * (obb.size.y * 0.5f);
   Vec3 forward = obb.orientations[2] * (obb.size.z * 0.5f);

   // 8頂点を計算
   Vec3 corners[8];
   int i = 0;
   for (int dy : {-1, 1}) {
      for (int dz : {-1, 1}) {
         for (int dx : {-1, 1}) {
            Math::Vector::Vec3 pos = *obb.center;

            Math::Vector::Vec3 vec = right * static_cast<float>(dx) + up * static_cast<float>(dy) + forward * static_cast<float>(dz);
            corners[i++] = vec;

         }
      }
   }

   // 辺（12本 × 2頂点）
   constexpr int edgeIndices[12][2] = {
       {0, 1}, {1, 3}, {3, 2}, {2, 0}, // 下面
       {4, 5}, {5, 7}, {7, 6}, {6, 4}, // 上面
       {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 側面
   };

   outLines.clear();
   outLines.resize(48);
   int index = 0;
   for (auto &edge : edgeIndices) {
      outLines[index++]=(corners[edge[0]]);
      outLines[index++]=(corners[edge[1]]);
   }
}

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
      vertices[i] = {obb.center->x + obb.orientations[0].x * sign.x * obb.size.x + obb.orientations[1].x * sign.y * obb.size.y + obb.orientations[2].x * sign.z * obb.size.z,
                     obb.center->y + obb.orientations[0].y * sign.x * obb.size.x + obb.orientations[1].y * sign.y * obb.size.y + obb.orientations[2].y * sign.z * obb.size.z,
                     obb.center->z + obb.orientations[0].z * sign.x * obb.size.x + obb.orientations[1].z * sign.y * obb.size.y + obb.orientations[2].z * sign.z * obb.size.z};
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
