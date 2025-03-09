#include "OutPutRay.h"

void CLEYERA::Model3d::system::OutPutRay::Init() {

   auto device = Base::DX::DXManager::GetInstance()->GetDevice();
   Math::Vector::Vec2 size = {float(Base::Win::WinApp::GetKWindowWidth()), float(Base::Win::WinApp::GetKWindowHeight())};

   buf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   buf_->SetDevice(device);
   buf_->Init();

   buf_->CreateTexture2d(size, DXGI_FORMAT_R8G8B8A8_UNORM, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_HEAP_TYPE_DEFAULT);

   D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
   uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
   buf_->RegisterUAV(uavDesc);

   ///
}