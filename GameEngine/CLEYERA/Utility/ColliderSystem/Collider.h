#pragma once

namespace CLEYERA {

namespace Util {

namespace Collider {

class Collider {
 public:
   Collider();
   virtual ~Collider();

   virtual bool HitCheck(const Collider &other) = 0;

   virtual void ColliderImGuiUpdate() = 0;

 private:




};

} // namespace Collider
} // namespace Util
} // namespace CLEYERA