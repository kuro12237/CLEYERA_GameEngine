#include "DebugScene.h"

void DebugScene::Init() {

   camera = std::make_unique<TestCamera>();
   camera->Create();

   //uint32_t handle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Tower", "Tower");

 
   object = std::make_shared<TestObject>();
   object->Init();

   
   objectList_.push_back(object->GetGameObject());
   InitRaytracing();

}

void DebugScene::Update() {

	object->Update();

   camera->Update();
}

void DebugScene::ImGuiUpdate() {

 


}
