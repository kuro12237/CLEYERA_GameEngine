#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"

#include "../../DX/DXBarrier/DXBarrier.h"

namespace CLEYERA {
namespace Model3d {
namespace system {


class Tlas {
 public:
   Tlas() {};
   ~Tlas() {};

   void Init();

   #pragma region Set

   void SetBlas(ID3D12Resource *buf) { blas_ = buf; }
#pragma endregion


 private:
  
std::unique_ptr<Base::DX::DXBufferResource<int32_t>> buf_ = nullptr;
   ID3D12Resource *blas_ = nullptr;

};


}
} // namespace Model3d
} // namespace CLEYERA