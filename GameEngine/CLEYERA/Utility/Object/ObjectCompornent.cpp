#include "ObjectCompornent.h"
#include "ObjectManager.h"

CLEYERA::Manager::ObjectComponent::ObjectComponent() {

   this->modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
   this->objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
   this->renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();

   uint32_t handleSphere = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/system/DebugSphere", "DebugSphere");

   modelHandle_ = handleSphere;

   this->gameObject_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObject_->Create(modelHandle_);
   gameObject_->SetScale(scale_);
   gameObject_->SetRotate(rotate_);
   gameObject_->SetTranslate(translate_);
   this->gameObject_->Update();


   objectManager_->AddObject(this->gameObject_);
   renderManager_->PushObj(this->gameObject_);
}

void CLEYERA::Manager::ObjectComponent::ImGuiUpdate() {



}

