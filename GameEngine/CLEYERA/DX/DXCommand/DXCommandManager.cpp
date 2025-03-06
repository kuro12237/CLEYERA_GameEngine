#include "DXCommandManager.h"
#include "../DXManager.h"

using namespace CLEYERA::Base::DX;

DXCommandManager *DXCommandManager::GetInstace() {

   static DXCommandManager instance;
   return &instance;
}

void CLEYERA::Base::DX::DXCommandManager::Init() {

   list_ = DXManager::GetInstance()->GetCommandList();
}

void CLEYERA::Base::DX::DXCommandManager::OMRenderTargets(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> &rtvHandles, const D3D12_CPU_DESCRIPTOR_HANDLE *dsvHandle) {

   if (list_) {
      list_->OMSetRenderTargets(static_cast<UINT>(rtvHandles.size()), rtvHandles.data(), false, dsvHandle);
   }
}

void CLEYERA::Base::DX::DXCommandManager::ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE handle, const std::vector<float> &clearColor) {
   if (list_ && clearColor.size() == 4) {
      list_->ClearRenderTargetView(handle, clearColor.data(), 0, nullptr);
   }
}
