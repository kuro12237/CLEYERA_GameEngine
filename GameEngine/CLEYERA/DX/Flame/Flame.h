#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class Flame {
 public:
   Flame() {};
   ~Flame() {};

   void Init();

   void Update();

   void ImGuiUpdate();

 private:
   std::chrono::steady_clock::time_point reference_ = {};

   float fps_ = 0.0f;
};

} // namespace DX
} // namespace Base
} // namespace CLEYERA