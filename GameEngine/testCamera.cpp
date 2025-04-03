#include "testCamera.h"

void TestCamera::Create() {
   camera_ = std::make_shared<CLEYERA::Util::Camera>();
   camera_->Init();

   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);

   CLEYERA::Manager::CameraManager::GetInstance()->SetCamera(this->camera_);
}

void TestCamera::Update() {

   ImGui::Begin("camera");

   ImGui::DragFloat3("r", &rotate_.x, 0.1f);
   ImGui::DragFloat3("t", &translate_.x, 1.0f);

   ImGui::End();

   camera_->Update();
}