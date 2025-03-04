#include "DXRTVDescripter.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXRTVDescripter::Create() {

  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();
  std::vector<ID3D12Resource *> swapResources;
  swapChain_ = dxManager_->GetSwapChain();
  commandList_ = dxManager_->GetCommandList();

  

  size_t resourceCount = swapChain_.lock()->GetSwapChainCount();
  swapResources.resize(resourceCount);

  for (size_t i = 0; i < resourceCount; i++) {

    swapResources[i] = swapChain_.lock()->GetSwapChainResource(i);
  }


  rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

  gpuHandles_.resize(this->descripterSize_);
  cpuHandles_.resize(this->descripterSize_);

  /// ハンドルのぽいんたげっと
  cpuStartHandle_ = descripter_->GetCPUDescriptorHandleForHeapStart();
  cpuHandles_[0] = cpuStartHandle_;

   for (size_t i = 0; i < resourceCount; i++) {
    device->CreateRenderTargetView(swapResources[i], &rtvDesc_, cpuHandles_[i]);
    if (i + 1 < resourceCount) {
      cpuHandles_[i + 1].ptr =
          cpuHandles_[i].ptr + device->GetDescriptorHandleIncrementSize(type_);
    }
  }
  NotifyObserversCreateComp();
}

void CLEYERA::Base::DX::DXRTVDescripter::Begin() {
  UINT backBufferIndex =
      swapChain_.lock()->GetSwapChain()->GetCurrentBackBufferIndex();

  commandList_->OMSetRenderTargets(1, &cpuHandles_[backBufferIndex], false,
                                   nullptr);
  float clearColor[] = {0.1f, 0.25f, 0.5f, 1.0f};

  commandList_->ClearRenderTargetView(cpuHandles_[backBufferIndex],
                                      clearColor, 0, nullptr);

}

void CLEYERA::Base::DX::DXRTVDescripter::End() {}
