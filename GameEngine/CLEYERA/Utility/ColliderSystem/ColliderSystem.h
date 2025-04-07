#pragma once

#include "../../pch/Pch.h"
#include "Collider.h"
#include "ColliderFunc.h"
#include "OBBCollider.h"

#include "../RenderManager/RenderManager.h"

namespace CLEYERA {

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

   void PushCollider(std::weak_ptr<Util::Collider::Collider> collider) { colliderList_.push_back(collider); }

 private:
   bool isLineDraw_ = true;

   std::list<std::weak_ptr<Util::Collider::Collider>> colliderList_;

#pragma region Single

   ColliderSystem() = default;
   ~ColliderSystem() = default;
   ColliderSystem(const ColliderSystem &) = delete;
   ColliderSystem &operator=(const ColliderSystem &) = delete;

#pragma endregion
};
} // namespace Manager
} // namespace CLEYERA