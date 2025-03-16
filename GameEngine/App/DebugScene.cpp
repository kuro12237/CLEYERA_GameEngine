#include "DebugScene.h"

void DebugScene::Init() {

   uint32_t handle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Tower", "Tower");

   uint32_t handleCube = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/DfCube", "DfCube");
 

   gameObj_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObj_->Create(handleCube);

   gameObj_->SetScale(scale_);
   gameObj_->SetRotate(rotate_);
   gameObj_->SetTranslate(translate_);

   gameObj_->TransformUpdate();

   this->objectList_.push_back(gameObj_);
 
   gameObjCube_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObjCube_->Create(handle);

   gameObjCube_->SetScale(scale_);
   gameObjCube_->SetRotate(rotate_);
   gameObjCube_->SetTranslate(translate_);

   gameObjCube_->TransformUpdate();

   this->objectList_.push_back(gameObjCube_);
   InitRaytracing();
}

void DebugScene::Update() {}

void DebugScene::ImGuiUpdate() {

   ImGui::Begin("a");

   ImGui::DragFloat3("t", &translate_.x, 0.5f);

   ImGui::End();
}
