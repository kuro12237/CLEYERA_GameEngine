#pragma once

#include "../../pch/Pch.h"
#include "AABBCollider.h"
#include "Collider.h"
#include "ColliderFunc.h"
#include "OBBCollider.h"

#include "../RenderManager/RenderManager.h"
#include "Octree/Octree.h"

namespace CLEYERA {

namespace Component {
class ObjectComponent;
}

namespace Manager {

/// <summary>
/// コライダーシステム
/// </summary>
class ColliderSystem {
public:
  static ColliderSystem *GetInstance() {
    static ColliderSystem instance;
    return &instance;
  }

  void ImGuiUpdate();

  void Update();

  void Clear() { objectList_.clear(); }

  void PushCollider(std::weak_ptr<Component::ObjectComponent> collider) {
    objectList_.push_back(collider);
  }

private:
  bool isLineDraw_ = true;

  std::list<std::weak_ptr<Component::ObjectComponent>> objectList_;

#pragma region Single

  ColliderSystem() = default;
  ~ColliderSystem() = default;
  ColliderSystem(const ColliderSystem &) = delete;
  ColliderSystem &operator=(const ColliderSystem &) = delete;

#pragma endregion
};
} // namespace Manager
} // namespace CLEYERA