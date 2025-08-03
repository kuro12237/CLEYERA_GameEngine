#include "GameClearScene.h"

GameClearScene::GameClearScene() {

 CLEYERA::Manager::ObjectManager::GetInstance()->LoadObjectData("test.json");
}

void GameClearScene::Init() {
  
  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("GameClearSceneData");

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData();

  loader_.reset();

  camera_ = std::make_unique<GameClearCamera>();
  camera_->Init();

  // 地形モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);

    sceneAnim_ = std::make_unique<SceneChangeAnim>();
  sceneAnim_->Init();
}

void GameClearScene::Update([[maybe_unused]] GameManager *g) {

  for (auto manager : managerComponents_) {

    auto mgr = manager.lock();
    mgr->Update();
  }

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

void GameClearScene::Draw2d() { sceneAnim_->Draw(); }
