#include "DebugScene.h"

void DebugScene::Init() {

   camera = std::make_unique<TestCamera>();
   camera->Create();

   uint32_t handle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Tower", "Tower");

   uint32_t handleCube = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/system/DebugSphere", "DebugSphere");

   gameObj_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObj_->Create(handleCube);

   gameObj_->SetScale(scale_);
   gameObj_->SetRotate(rotate_);
   gameObj_->SetTranslate(translate_);
 
   gameObj_->TransformUpdate();

   // this->objectList_.push_back(gameObj_);

   gameObjCube_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   gameObjCube_->Create(handle);

   gameObjCube_->SetScale(scaleCube_);
   gameObjCube_->SetRotate(rotateCube_);
   gameObjCube_->SetTranslate(translateCube_);

   gameObjCube_->TransformUpdate();

   this->objectList_.push_back(gameObjCube_);

   line_ = std::make_shared<CLEYERA::Model3d::Line3d>();
   line_->Init(64);
   line_->SetLinePos(positions_);
   positions_.resize(128);

   InitRaytracing();

   CLEYERA::Manager::RenderManager::GetInstance()->PushObj(gameObjCube_);
   CLEYERA::Manager::RenderManager::GetInstance()->PushLine3d(line_);

   CLEYERA::Manager::RenderManager::GetInstance()->PushObj(gameObj_);
}

void DebugScene::Update() {

   //line_->Update();
   gameObj_->Update();
   gameObjCube_->Update();
   camera->Update();
}

void DebugScene::ImGuiUpdate() {

   ImGui::Begin("Obj");

   ImGui::DragFloat3("s", &scale_.x, 0.5f);
   ImGui::DragFloat3("r", &rotate_.x, 0.5f);
   ImGui::DragFloat3("t", &translate_.x, 0.5f);
   ImGui::End();

   ImGui::Begin("ObjCube");

   ImGui::DragFloat3("s", &scaleCube_.x, 0.5f);
   ImGui::DragFloat3("r", &rotateCube_.x, 0.5f);
   ImGui::DragFloat3("t", &translateCube_.x, 0.5f);

   ImGui::End();


}
