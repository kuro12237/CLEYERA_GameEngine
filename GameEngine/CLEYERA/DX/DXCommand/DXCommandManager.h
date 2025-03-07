#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXCommandManager {
 public:
   static DXCommandManager *GetInstace();

   void Init();

   void OMRenderTargets(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> &rtvHandles, const D3D12_CPU_DESCRIPTOR_HANDLE *dsvHandle);

   void ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE handle, const std::vector<float> &clearColor);

   void ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_CLEAR_FLAGS flag);

   void SetViewCommand(int32_t kWidth,int32_t height);
   void SetScissorCommand(int32_t kWidth, int32_t height);

   void SetDescripterHeap(const std::vector<ID3D12DescriptorHeap *> desc);


#pragma region Set

   void SetCommandList(ID3D12GraphicsCommandList *list) { list_ = list; }

#pragma endregion

 private:
  
   ID3D12GraphicsCommandList *list_ = nullptr;

   DXCommandManager() = default;
   ~DXCommandManager() = default;
   DXCommandManager(const DXCommandManager &) = delete;
   DXCommandManager &operator=(const DXCommandManager &) = delete;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA