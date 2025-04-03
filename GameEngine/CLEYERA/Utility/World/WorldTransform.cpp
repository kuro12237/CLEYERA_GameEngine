#include "WorldTransform.h"

void CLEYERA::Util::WorldTransform::WTCreate(const uint32_t &instanceNum) {

   camera_ = &Manager::CameraManager::GetInstance()->GetCamera().lock()->GetForGpu();

   this->instanceNum_ = &instanceNum;
   mat_.Identity();

   buf_ = std::make_shared<Base::DX::DXBufferResource<Util::system::forWorldMat>>();
   buf_->Init();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);

   ConvertMat();
}

void CLEYERA::Util::WorldTransform::ConvertMat() {
   forGpuWorldMat_.worldMat_ = mat_;
   forGpuWorldMat_.worldMatInv_ = forGpuWorldMat_.worldMat_.Inverse();
   forGpuWorldMat_.VPV_ = Math::Matrix::Func::Multiply(forGpuWorldMat_.worldMat_, camera_->mtxVP_);
}

void CLEYERA::Util::WorldTransform::SetWorldTransfar() {

   buf_->Map();
   buf_->SetParam(forGpuWorldMat_);

   buf_->Update();
}

void CLEYERA::Util::WorldTransform::BindWT(UINT num) { buf_->GraphicsCommand(num); }
