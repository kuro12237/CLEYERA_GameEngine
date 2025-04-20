#pragma once
#include "../Collider.h"
#include "pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class Octree {
 public:
   Octree() {};
   ~Octree() = default;

   // Collider の挿入
   void Insert(const std::weak_ptr<Collider> &collider);

   // 領域内の Collider を検索
   std::vector<std::weak_ptr<Collider>> Query(const Math::Vector::Vec3 &min, const Math::Vector::Vec3 &max) const;

   void SetCenter(const Math::Vector::Vec3 &pos) { center_ = pos; }
   void SetSize(float size) { size_ = size; }
   void SetLevel(int level) { level_ = level; }

 private:
   Math::Vector::Vec3 center_ = {}; // 空間の中心
   float size_ = 640.0f;           // 空間のサイズ
   int level_ = 1;                  // 分割レベル

   std::vector<std::weak_ptr<Collider>> colliders_; // このノードに格納されている Collider
   std::vector<std::unique_ptr<Octree>> children_;    // 子ノード

   // 子ノードを生成
   void CreateChildren();

   // 領域内に位置が含まれるかを判定
   bool IsInside(const Math::Vector::Vec3 &position) const;

   // 領域と交差しているかを判定
   bool Intersects(const Math::Vector::Vec3 &min, const Math::Vector::Vec3 &max) const;
};
} // namespace Collider
} // namespace Util
} // namespace CLEYERA