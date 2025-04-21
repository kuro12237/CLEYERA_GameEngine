#pragma once
#include "../../3d/Line3d/Line3d.h"
#include "ColliderFunc.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

enum class ColliderType { OBB };

/// <summary>
/// コライダー
/// </summary>
class Collider {
 public:
   Collider() {};
   virtual ~Collider() {};

   bool HitCall(Collider *other);

   virtual void ColliderImGuiUpdate() = 0;

   ColliderType GetColliderType() const { return type_; }

   virtual void Create() = 0;

   virtual void Update() = 0;

   std::shared_ptr<CLEYERA::Model3d::Line3d> GetLine() { return line_; }

   virtual void ColliderImGuiUpdate(const std::string &name) = 0;

   virtual void HitCallFunc(const Collider &other) = 0;

   Math::Vector::Vec3 GetCenter() { return center_; }

 private:
 protected:
   ColliderType type_ = ColliderType::OBB;

   std::shared_ptr<CLEYERA::Model3d::Line3d> line_ = nullptr;
   std::vector<Math::Vector::Vec3> positions_ = {};

   std::vector<Math::Vector::Vec4> colors_ = {};

   Math::Vector::Vec3 center_{};

   Math::Matrix::Mat4x4 worldMatrix_ = {};
   bool isHit_ = false;

};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA