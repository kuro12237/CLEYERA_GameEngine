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

   sceneAnim_ = std::make_unique<SceneChangeAnim>();
  sceneAnim_->Init();
}

void GameOverScene::Update([[maybe_unused]] GameManager *g) {

  sceneAnim_->Update();

  auto input = CLEYERA::Manager::InputManager::GetInstance();
  if (input->PushBotton(XINPUT_GAMEPAD_A)) {

    sceneAnim_->Start();
  }
  if (sceneAnim_->IsEnd()) {
    g->ChangeScene(std::make_unique<TitleScene>());
    return;
  }


}

void GameOverScene::Draw2d() { sceneAnim_->Draw(); }
