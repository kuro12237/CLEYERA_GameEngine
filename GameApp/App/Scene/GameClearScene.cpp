#include "GameClearScene.h"

void GameClearScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("GameClearSceneData");

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);
}

void GameClearScene::Update([[maybe_unused]] GameManager *g) {

  for (auto manager : managerComponents_) {

    auto mgr = manager.lock();
    mgr->Update();
  }
}

void GameClearScene::Draw2d() {}
