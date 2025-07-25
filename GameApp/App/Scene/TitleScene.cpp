#include "TitleScene.h"

void TitleScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TitleSceneData");

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);
}

void TitleScene::Update([[maybe_unused]] GameManager *g) {

}

void TitleScene::Draw2d() {}
