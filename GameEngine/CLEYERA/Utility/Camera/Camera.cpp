#include "Camera.h"

void CLEYERA::Util::Camera::Init() {

   this->matProj_ = Math::Matrix::Func::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
   this->matView_.Identity();
   this->mat_.Identity();

   SetScale(dfScale);
}

void CLEYERA::Util::Camera::Update() {}
