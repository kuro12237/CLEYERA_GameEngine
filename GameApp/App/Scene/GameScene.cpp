#include "GameScene.h"
#include "../GameManager/GameManager.h"

GameScene::GameScene() {
  CLEYERA::Manager::ObjectManager::GetInstance()->LoadObjectData("test.json");

  itemManager_ = std::make_shared<ItemManager>();
  playerManager_ = std::make_shared<PlayerManager>();
}

void GameScene::Init() {
  uis_.resize(2);

  //読み込み
  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TestData");

  CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");

  managerComponents_.push_back(itemManager_);
  managerComponents_.push_back(playerManager_);

  enemyManager_ = std::make_shared<EnemyManager>();
  enemyManager_->SetPlayerManager(playerManager_.get());
  managerComponents_.push_back(enemyManager_);

  wallManager_ = std::make_shared<WallManager>();
  managerComponents_.push_back(wallManager_);

  playerManager_->SetPtr(itemManager_, enemyManager_);

  CLEYERA::Manager::ObjectManager::GetInstance()->Update();

  // 初期化
  for (auto manager : managerComponents_) {
    manager.lock()->Init();
  }

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  uiState_ = std::make_unique<PlayUIState>();
  uiState_->SetScene(this);
  uiState_->Init();

  // spriteの初期化
  for (auto s : spriteComponents_) {

    s.lock()->Init();
  }

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);

}

void GameScene::Update([[maybe_unused]] GameManager *g) {

  uiState_->Update();

  for (const auto &m : this->managerComponents_) {
    m.lock()->Update();
    m.lock()->CollectAllManagers();
  }

  // sprite更新
  std::list<std::string> spNames;
  for (auto s : spriteComponents_) {

#ifdef _DEBUG

    if (s.lock()->GetName() != "") {
      for (std::string name : spNames) {
        if (name == s.lock()->GetName()) {
          // 同じものが複数回呼び出されてる
          assert(0);
        }
      }
    }
#endif // _DEBUG
    s.lock()->Update();
    spNames.push_back(s.lock()->GetName());
  }
}

void GameScene::Draw2d() { 
    uiState_->Draw2d();
  }
