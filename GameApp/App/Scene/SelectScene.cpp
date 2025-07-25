#include "SelectScene.h"

void SelectScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("SelectSceneData");

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);
}

void SelectScene::Update([[maybe_unused]] GameManager *g) {

}

void SelectScene::Draw2d() {}
