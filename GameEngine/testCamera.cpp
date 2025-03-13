#include "testCamera.h"

void TestCamera::Create() {
   camera_ = std::make_unique<CLEYERA::Util::Camera>();
   camera_->Init();

   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);
}

void TestCamera::Update() {

   ImGui::Begin("camera");

   ImGui::DragFloat3("r", &rotate_.x, 0.1f);
   ImGui::DragFloat3("t", &translate_.x, 1.0f);

   ImGui::End();

   camera_->Update();
}