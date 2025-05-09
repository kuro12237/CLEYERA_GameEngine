#include "testCamera.h"

void TestCamera::Create() {
   camera_ = std::make_shared<CLEYERA::Util::Camera>();
   camera_->Init();

   translate_.y = 4.0f;
   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);

   CLEYERA::Manager::CameraManager::GetInstance()->SetCamera(this->camera_);
}

void TestCamera::Update() {

   ImGui::Begin("camera");

   ImGui::DragFloat3("r", &degreeRotate_.x, 1.0f);
   rotate_.x = Math::Vector::Func::degreesToRadians(degreeRotate_.x);
   rotate_.y = Math::Vector::Func::degreesToRadians(degreeRotate_.y);
   rotate_.z = Math::Vector::Func::degreesToRadians(degreeRotate_.z);
   


   ImGui::DragFloat3("t", &translate_.x, 1.0f);

   ImGui::End();

   camera_->Update();
}