#include "TitleScene.h"
#include <EditorObject/ABotton/ABotton.h>

void TitleScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TitleSceneData");

  std::shared_ptr<ABotton> abotton = std::make_shared<ABotton>();
  abotton->SetTitleScene(this);
  objectManager_->CreateObject<ABotton>("bota", abotton);

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

void TitleScene::Update([[maybe_unused]] GameManager *g) {

  sceneAnim_->Update();

  auto input = CLEYERA::Manager::InputManager::GetInstance();
  if (input->PushBotton(XINPUT_GAMEPAD_A) == true ||
      input->PushKey(DIK_SPACE) == true) {

    isStart_ = true;
  }

  if (isEndProcess_) {

    sceneAnim_->Start();
  }

  if (sceneAnim_->IsEnd()) {
    g->ChangeScene(std::make_unique<GameScene>());
    return;
  }
}

void TitleScene::Draw2d() { sceneAnim_->Draw(); }
