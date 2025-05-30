#include "GameScene.h"

void GameScene::Init() {

   loader_ = std::make_unique<SceneLoader>();
   loader_->LoadSceneData("TestData");

   CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");
   uint32_t bulletNum = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
   bulletNum;
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Enemy2", "Enemy2");
   modelHandle;
   playerManager_ = std::make_shared<PlayerManager>();
   managerCompornents_.push_back(playerManager_);

   enemyManager_ = std::make_shared<EnemyManager>();
   enemyManager_->SetPlayerManager(playerManager_.get());
   managerCompornents_.push_back(enemyManager_);

   wallManager_ = std::make_shared<WallManager>();
   managerCompornents_.push_back(wallManager_);

   // 初期化
   for (auto manager : managerCompornents_) {
      manager->Init();
      // マネージャーのGameObjListをSceneにも登録(weak)
      for (auto obj : manager->GetObjList()) {

         // 絶対に登録
         objectComponents_.push_back(obj);
         objectList_.push_back(obj->GetGameObject());
         

         // 重力適用
         gravityManager_->PushData(obj);
         // 地形当たり判定適用
         terrain_->PushData(obj);


         if (obj->GetCollder().lock()) {
           collidersystem_->PushCollider(obj);
         }
      }
   }


   // エディタのデータを各オブジェクトにセット
   enviromentObjs_ = loader_->SettingData(objectComponents_);
   loader_.reset();

   // 地形モデルの設定
   uint32_t modelHandlet = modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
   terrain_->ChengeData(modelHandlet);

   // 無視
   InitRaytracing();
}

void GameScene::Update() {

    for ( auto obj : enviromentObjs_ )
    {
      obj->Update();

    }
   for (auto manager : managerCompornents_) {

      manager->Update();
   }
}
