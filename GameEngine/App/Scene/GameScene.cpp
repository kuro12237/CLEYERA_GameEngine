#include "GameScene.h"

void GameScene::Init() {

    CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");

    playerManager_ = std::make_unique<PlayerManager>();

   managerCompornents_.push_back(playerManager_);

   for (auto manager : managerCompornents_) {
      manager->Init();
      for (auto obj : manager->GetObjList()) {

         objectList_.push_back(obj->GetGameObject());

         gravityManager_->PushData(obj);
         terrain_->PushData(obj);
      }
   }

   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Terrain/","terrain");
   terrain_->ChengeData(modelHandle);

   InitRaytracing();
}

void GameScene::Update() {
   for (auto manager : managerCompornents_) {

       manager->Update();
   }


}

