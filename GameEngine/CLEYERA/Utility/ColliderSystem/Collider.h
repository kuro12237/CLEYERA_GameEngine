#pragma once
#include "../../3d/Line3d/Line3d.h"
#include "ColliderFunc.h"

namespace CLEYERA {

namespace Component {

class ObjectComponent;
}

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

  bool HitCall(std::weak_ptr<Component::ObjectComponent> other);

  virtual void ColliderImGuiUpdate() = 0;

  ColliderType GetColliderType() const { return type_; }

  virtual void Create() = 0;
  virtual void Update() = 0;
  virtual void ColliderImGuiUpdate(const std::string &name) = 0;
  virtual Math::Vector::Vec3 CalcOverlapAABB(std::weak_ptr<Collider> other) = 0;

  std::weak_ptr<CLEYERA::Model3d::Line3d> GetLine() const { return line_; }
  Math::Vector::Vec3 GetCenter() { return center_; }

  /// <summary>
  /// 当たった時の関数ポインタのセッター
  /// </summary>
  void SetHitCallFunc(
      std::function<void(std::weak_ptr<Component::ObjectComponent>)> func) {
    HitCallFunc = std::move(func);
  }

private:
  std::function<void(std::weak_ptr<Component::ObjectComponent> other)>
      HitCallFunc;

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