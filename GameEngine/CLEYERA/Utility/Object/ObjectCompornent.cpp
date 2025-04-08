#include "ObjectCompornent.h"
#include "ObjectManager.h"

CLEYERA::Manager::ObjectComponent::ObjectComponent() {

   this->modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
   this->objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
   this->renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();
   this->inputManager_ = CLEYERA::Manager::InputManager::GetInstance();

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

         ImGui::DragFloat3("Scale", &scale_.x, 0.01f);
         ImGui::DragFloat3("Rotate", &rotate_.x, 0.01f);
         ImGui::DragFloat3("Translate", &translate_.x, 0.01f);
         ImGui::TreePop();
      }

      if (ImGui::TreeNode("force")) {
         ImGui::DragFloat("friction", &friction_, 0.1f, 0.0f, 1.0f);
         ImGui::DragFloat("mass", &mass_, 0.1f, 0.1f, 20.0f);
         ImGui::TreePop();
      }

      if (collider_) {
         collider_->ColliderImGuiUpdate(name_);
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Manager::ObjectComponent::TransformUpdate() {
   //isTerrainHit_ = false;
   using Vec3 = Math::Vector::Vec3;

    Vec3 totalForce = force_;
   ////+gravityforce_;

   //// 加速度 = 力 / 質量（F = ma → a = F/m）
    Vec3 acceleration = {};
    if (mass_ != 0.0f && mass_ >= 0.0f) {
       acceleration = totalForce * (1.0f / mass_);
    }

   // 積分：速度と位置の更新
    velocity_ = velocity_ + acceleration; // v = v0 + at
   translate_.x += velocity_.x; // p = p0 + vt
   translate_.y += velocity_.y;
   translate_.z += velocity_.z;
   // 摩擦（速度減衰）
   velocity_ = velocity_ * friction_; // FPS依存で調整
}

void CLEYERA::Manager::ObjectComponent::GravityUpdate(const float &g) {

      velocity_.y += g;
  
}

void CLEYERA::Manager::ObjectComponent::TerrainHit(const Math::Vector::Vec3 &pos) {
   velocity_.y = velocity_.y * -bounceFactor_;

   // velocity_.y = 0.0f;
   translate_ = pos;
   // gameObject_->WorldMatUpdate();
   isTerrainHit_ = true;
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
