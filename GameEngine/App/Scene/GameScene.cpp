#include "GameScene.h"
#include "../GameManager/GameManager.h"

void GameScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TestData");

  CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");
  uint32_t bulletNum = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
  bulletNum;


  playerManager_ = std::make_shared<PlayerManager>();
  managerCompornents_.push_back(playerManager_);

  enemyManager_ = std::make_shared<EnemyManager>();
  enemyManager_->SetPlayerManager(playerManager_.get());
  managerCompornents_.push_back(enemyManager_);

  wallManager_ = std::make_shared<WallManager>();
  managerCompornents_.push_back(wallManager_);

  imgui_ = std::make_shared<TestPlayGui>();
  imgui_->SetPlayerHp(playerManager_->GetHp());
  imgui_->SetEnemyCount(enemyManager_->GetEnemyCount());

  managerCompornents_.push_back(imgui_);

  // 初期化
  for (auto manager : managerCompornents_) {
    manager.lock()->Init();
    // マネージャーのGameObjListをSceneにも登録(weak)
    for (auto obj : manager.lock()->GetObjList()) {

      // 絶対に登録
      objectComponents_.push_back(obj);
      objectList_.push_back(obj.lock()->GetGameObject());

      // 重力適用
      gravityManager_->PushData(obj);
      // 地形当たり判定適用
      terrain_->PushData(obj);
    }
    manager.lock()->GetObjList().clear();
  }

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData(objectComponents_);

  for (auto obj : enviromentObjs_) {
    objectComponents_.push_back(obj);
  }

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandlet = modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandlet);

  // 無視
  InitRaytracing();
}

void GameScene::Update([[maybe_unused]] GameManager *g) {

  if (imgui_->ResetScene()) {
    g->ChangeScene(std::make_unique<GameScene>());

    return;
  }

  for (auto manager : managerCompornents_) {

    auto mgr = manager.lock();
    mgr->CollectAllObjects(objectComponents_);
  }

  for (auto obj : objectComponents_) {

    obj.lock()->Update();
  }
}
