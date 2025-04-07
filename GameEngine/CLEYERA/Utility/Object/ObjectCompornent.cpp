#include "ObjectCompornent.h"
#include "ObjectManager.h"

CLEYERA::Manager::ObjectComponent::ObjectComponent() {

   this->modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
   this->objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
   this->renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();

   uint32_t handleSphere = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/system/Sphere", "Sphere");

   modelHandle_ = handleSphere;

   this->gameObject_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObject_->Create(modelHandle_);
   gameObject_->SetScale(scale_);
   gameObject_->SetRotate(rotate_);
   gameObject_->SetTranslate(translate_);
   gameObject_->SetName(name_);
   this->gameObject_->Update();

   objectManager_->AddObject(this->gameObject_);
   renderManager_->PushObj(this->gameObject_);
}

void CLEYERA::Manager::ObjectComponent::ImGuiUpdate() {

   if (ImGui::TreeNode(name_.c_str())) {

      if (ImGui::TreeNode("Transform")) {

         ImGui::DragFloat3("Scale", &scale_.x);
         ImGui::DragFloat3("Rotate", &rotate_.x);
         ImGui::DragFloat3("Translate", &translate_.x);
         ImGui::TreePop();
      }

      if (collider_) {
         collider_->ColliderImGuiUpdate(name_);
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Manager::ObjectComponent::CreateCollider(Util::Collider::ColliderType type) {

   if (type == Util::Collider::ColliderType::OBB) {
      collider_ = std::make_shared<CLEYERA::Util::Collider::OBBCollider>();
      collider_->SetCenter(&translate_);
      collider_->SetRotate(&rotate_);
      collider_->SetWorldMatrix(&gameObject_->GetMat());
      collider_->Create();

      colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();
      colliderSystem_->PushCollider(collider_);
   }
}
