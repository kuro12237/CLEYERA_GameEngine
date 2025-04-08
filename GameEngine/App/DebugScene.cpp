#include "DebugScene.h"

void DebugScene::Init() {

   camera = std::make_unique<TestCamera>();
   camera->Create();

   object = std::make_shared<TestObject>();
   object->SetName("a");
   object->Init();

   objectb = std::make_shared<TestObject>();
   objectb->SetName("b");
   objectb->Init();

   gravityManager_->PushData(object);
   gravityManager_->PushData(objectb);
   terrain_->PushData(object);
   terrain_->PushData(objectb);

   objectList_.push_back(object->GetGameObject());
   InitRaytracing();
}

void DebugScene::Update() {

   objectb->Update();
   object->Update();

   camera->Update();
}

void DebugScene::ImGuiUpdate() {}
