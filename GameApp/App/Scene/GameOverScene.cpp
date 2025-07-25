#include "GameOverScene.h"

void GameOverScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("GameOverSceneData");

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);
}

void GameOverScene::Update([[maybe_unused]] GameManager *g) {}

void GameOverScene::Draw2d() {}
