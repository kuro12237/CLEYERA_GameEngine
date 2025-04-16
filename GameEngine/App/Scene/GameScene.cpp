#include "GameScene.h"

void GameScene::Init() {

   loader_ = std::make_unique<SceneLoader>();
   loader_->LoadSceneData("TestData");

   CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");

   playerManager_ = std::make_unique<PlayerManager>();
   managerCompornents_.push_back(playerManager_);

   // 初期化
   for (auto manager : managerCompornents_) {
      manager->Init();
      // マネージャーのGameObjListをSceneにも登録(weak)
      for (auto obj : manager->GetObjList()) {

         // 無視
         objectList_.push_back(obj->GetGameObject());

         // 重力適用
         gravityManager_->PushData(obj);
         // 地形当たり判定適用
         terrain_->PushData(obj);
      }
   }

   // 地形モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
   terrain_->ChengeData(modelHandle);

   // 無視
   InitRaytracing();
}

void GameScene::Update() {
   for (auto manager : managerCompornents_) {

      manager->Update();
   }
}
