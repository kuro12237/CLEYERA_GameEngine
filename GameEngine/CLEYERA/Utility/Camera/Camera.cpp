#include "Camera.h"

void CLEYERA::Util::Camera::Init() {

   this->matProj_ = Math::Matrix::Func::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
   this->matView_.Identity();
   this->mat_.Identity();

   SetScale(dfScale);

   buf_ = std::make_shared<Base::DX::DXBufferResource<system::SCamera>>();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());
   buf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
}

void CLEYERA::Util::Camera::Update() {
   mat_ = Math::Matrix::Func::AffineMatrix(dfScale, *rotate_, *translate_);

   mtxViewInv_ = mat_;
   matView_ = mat_.Inverse();
   matProj_ = Math::Matrix::Func::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
   mtxProjInv_ = matProj_.Inverse();

   ConvertData();

   buf_->Map();
   buf_->SetParam(forGpu_);
   buf_->UnMap();
}

void CLEYERA::Util::Camera::ConvertData() {

   forGpu_.matProj_ = matProj_;
   forGpu_.mtxProjInv_ = mtxProjInv_;
   forGpu_.matView_ = matView_;
   forGpu_.mtxViewInv_ = mtxViewInv_;
}
