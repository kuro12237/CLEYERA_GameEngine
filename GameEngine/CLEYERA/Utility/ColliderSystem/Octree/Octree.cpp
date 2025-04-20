#include "Octree.h"
#include <iostream>

using namespace CLEYERA::Util::Collider;

void Octree::Insert(const std::weak_ptr<Collider> &collider) {
   if (!IsInside(collider.lock()->GetCenter())) {
      return; // 空間外の Collider は無視
   }

   if (level_ == 0 || size_ <= 1.0f) {
      colliders_.push_back(collider); // このノードに格納
      return;
   }

   if (children_.empty()) {
      CreateChildren(); // 必要に応じて子ノードを生成
   }

   for (auto &child : children_) {
      if (child->IsInside(collider.lock()->GetCenter())) {
         child->Insert(collider);
         return;
      }
   }

   // どの子ノードにも属さない場合、このノードに格納
   colliders_.push_back(collider);
}

std::vector<std::weak_ptr<Collider>> Octree::Query(const Math::Vector::Vec3 &min, const Math::Vector::Vec3 &max) const {
   std::vector<std::weak_ptr<Collider>> result;
   min, max;
   if (!Intersects(min, max)) {
      return result; // このノードと領域が交差しない場合
   }

   // このノードの Collider を追加
   for (auto collider : colliders_) {

      result.push_back(collider);
   }
   // 子ノードを再帰的に検索
   for (auto &child : children_) {
      if (child) {
         auto childResults = child->Query(min, max);
         result.insert(result.end(), childResults.begin(), childResults.end());
     

      }
   }

  
   return result;
}

void Octree::CreateChildren() {
   float childSize = size_ / 2.0f;
   for (int i = 0; i < 8; ++i) {
      Math::Vector::Vec3 offset((i & 1 ? 1 : -1) * childSize / 2, (i & 2 ? 1 : -1) * childSize / 2, (i & 4 ? 1 : -1) * childSize / 2);
      std::unique_ptr<Octree> oct = std::make_unique<Octree>();
      oct->SetCenter(center_ + offset);
      oct->SetSize(childSize);
      oct->SetLevel(level_ - 1);

      children_.emplace_back(std::move(oct));
   }
}

bool Octree::IsInside(const Math::Vector::Vec3 &position) const {
   return position.x >= center_.x - size_ / 2 && position.x <= center_.x + size_ / 2 && position.y >= center_.y - size_ / 2 && position.y <= center_.y + size_ / 2 && position.z >= center_.z - size_ / 2 && position.z <= center_.z + size_ / 2;
}

bool Octree::Intersects(const Math::Vector::Vec3 &min, const Math::Vector::Vec3 &max) const {
   Math::Vector::Vec3 nodeMin = center_ - Math::Vector::Vec3(size_ / 2,size_ / 2,size_ / 2);
   Math::Vector::Vec3 nodeMax = center_ + Math::Vector::Vec3(size_ / 2,size_ / 2,size_ / 2);

   return !(nodeMax.x < min.x || nodeMin.x > max.x || nodeMax.y < min.y || nodeMin.y > max.y || nodeMax.z < min.z || nodeMin.z > max.z);
}
