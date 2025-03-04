#include "DXRTVDescripter.h"
#include "../DXManager.h"

void CLEYERA::Base::DX::DXRTVDescripter::Create() {

  dxManager_ = DXManager::GetInstance();
  ID3D12Device5 *device = dxManager_->GetDevice();

  type_ = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

  CreateDescripter(type_, false);

  rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

  ///ハンドルのぽいんたげっと
  //rtvCPUStartHandle_ = descripter_->GetCPUDescriptorHandleForHeapStart();
  //rtvGPUStartHandle_ = descripter_->GetGPUDescriptorHandleForHeapStart();
  device;
  rtvGPUHandles_.resize(this->descripterSize_);

}
