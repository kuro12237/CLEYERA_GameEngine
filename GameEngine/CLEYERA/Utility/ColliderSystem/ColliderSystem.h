#pragma once

#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// コライダーシステム
/// </summary>
class ColliderSystem {
 public:
   ColliderSystem() {};
   ~ColliderSystem() {};

   void Init();

   void Update();

   void LineRender();

 private:

};
} // namespace Manager
} // namespace CLEYERA