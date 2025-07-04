#include "GameScene.h"
#include "../GameManager/GameManager.h"

GameScene::GameScene()
{
    itemManager_ = std::make_shared<ItemManager>();
    playerManager_ = std::make_shared<PlayerManager>(itemManager_);
}

void GameScene::Init() {
  uis_.resize(2);

  for (size_t i = 0; i < 1; i++) {

    std::shared_ptr<TestUI> ui = std::make_shared<TestUI>();
    ui->Init();
    uis_[i] = std::move(ui);
  }
  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TestData");

  CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");
  uint32_t bulletNum = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
  bulletNum;

  managerCompornents_.push_back(itemManager_);
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

    for (auto objs : mgr->GetObjList()) {
      auto it = objs.lock();
      if (!it)
        return;

      if (it) {
        objectComponents_.push_back(it);
      }
    }

    // ObjList をクリア（元の manager 側から削除）
    mgr->GetObjList().clear();
    mgr->Update();
    mgr->CollectAllObjects(objectComponents_);
  }

  // コンポーネントがからの場合削除
  for (auto it = objectComponents_.begin(); it != objectComponents_.end();) {
    if (it->expired()) {
      it = objectComponents_.erase(it);
    } else {
      ++it;
    }
  }

  std::list<std::string> objNames;

  for (auto obj : objectComponents_) {

    if (!obj.lock()) {
      continue;
    }

    for (std::string name : objNames) {

      if (name == obj.lock()->GetName()) {
        // 同じものが複数回呼び出されてる
        assert(0);
      }
    }

    obj.lock()->Update();

    objNames.push_back(obj.lock()->GetName());
  }
  for (size_t i = 0; i < 1; i++) {

    uis_[i]->Update();
  }
}

void GameScene::Draw2d() {

  for (size_t i = 0; i < 1; i++) {

    //uis_[i]->Draw();
  }
}

