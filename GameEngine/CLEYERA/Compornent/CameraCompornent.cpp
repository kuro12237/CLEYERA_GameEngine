#include "CameraCompornent.h"

CLEYERA::Component::CameraCompornent::CameraCompornent() {

   cameraManager_ = CLEYERA::Manager::CameraManager::GetInstance();

   camera_ = std::make_shared<CLEYERA::Util::Camera>();
   camera_->Init();
   camera_->SetRotate(rotate_);
   camera_->SetTranslate(translate_);
}

void CLEYERA::Component::CameraCompornent::ImGuiUpdate() {

   if (ImGui::TreeNode(name_.c_str())) {

      if (ImGui::TreeNode("Transform")) {

         ImGui::DragFloat3("R", &rotate_.x, 0.1f);
         ImGui::DragFloat3("T", &translate_.x, 0.1f);

         ImGui::TreePop();
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Component::CameraCompornent::CameraChange() { cameraManager_->SetCamera(camera_); }
