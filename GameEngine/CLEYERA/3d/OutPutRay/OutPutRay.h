#pragma once
#include "../../DX/DXBarrier/DXBarrier.h"
#include "../../DX/DXManager.h"
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

class OutPutRay {
 public:
   OutPutRay() {};
   ~OutPutRay() {};

   void Init();

 private:

   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> buf_ = nullptr;

};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA