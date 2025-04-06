#pragma once

#include "Collider.h"
#include "SCollider.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

class OBBCollider : public Collider {
 public:
   OBBCollider() {};
   ~OBBCollider() {};

   void ColliderImGuiUpdate() override;

   const system::OBB &GetOBB() const { return *obb_; }

 private:
   system::OBB *obb_ = nullptr;
};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA