#include "DXCommandManager.h"
#include "../DXManager.h"

using namespace CLEYERA::Base::DX;

DXCommandManager *DXCommandManager::GetInstace() {

   static DXCommandManager instance;
   return &instance;
}

void CLEYERA::Base::DX::DXCommandManager::Init() { list_ = DXManager::GetInstance()->GetCommandList(); }

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

void CLEYERA::Base::DX::DXCommandManager::ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_CLEAR_FLAGS flag) {

   if (list_) {
      list_->ClearDepthStencilView(handle, flag, 1.0f, 0, 0, nullptr);
   }
}

void CLEYERA::Base::DX::DXCommandManager::SetViewCommand(int32_t width, int32_t height) {

   D3D12_VIEWPORT viewport = {};

   viewport.Width = float(width);
   viewport.Height = float(height);
   viewport.TopLeftX = 0;
   viewport.TopLeftY = 0;
   viewport.MinDepth = 0.0f;
   viewport.MaxDepth = 1.0f;

   list_->RSSetViewports(1, &viewport);
}

void CLEYERA::Base::DX::DXCommandManager::SetScissorCommand(int32_t width, int32_t height) {

   D3D12_RECT scissorRect{};
   scissorRect.left = 0;
   scissorRect.right = width;
   scissorRect.top = 0;
   scissorRect.bottom = height;

   list_->RSSetScissorRects(1, &scissorRect);
}

void CLEYERA::Base::DX::DXCommandManager::SetDescripterHeap(const std::vector<ID3D12DescriptorHeap *> desc) {

    list_->SetDescriptorHeaps(static_cast<UINT>(desc.size()), desc.data());

}
