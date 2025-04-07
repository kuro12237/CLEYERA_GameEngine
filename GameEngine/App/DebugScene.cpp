#include "DebugScene.h"

void DebugScene::Init() {

   camera = std::make_unique<TestCamera>();
   camera->Create();

   // uint32_t handle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Tower", "Tower");

   object = std::make_shared<TestObject>();
   object->SetName("a");
   object->Init();

   objectb = std::make_shared<TestObject>();
   objectb->SetName("b");
   objectb->Init();

   objectList_.push_back(object->GetGameObject());
   InitRaytracing();
}

void DebugScene::Update() {

   objectb->Update();
   object->Update();

   camera->Update();
}

void DebugScene::ImGuiUpdate() {}
