#include "DebugSelectScene.h"

#include "SelectScene.h"

void DebugSelectScene::Init() {
  // シーン名リストを初期化
  sceneNames_ = {"TitleScene", "GameScene", "GameOverScene", "GameClearScene","SelectScene"};
  selectedIndex_ = 0;
  //InitRaytracing();
}

void DebugSelectScene::Update([[maybe_unused]] GameManager *g) {

  ImGui::Begin("SceneSelect");

  // Combo用にconst char*配列を作成
  std::vector<const char *> items;
  for (const auto &name : sceneNames_) {
    items.push_back(name.c_str());
  }

  // Combo表示
  ImGui::Combo("Scene", &selectedIndex_, items.data(),
               static_cast<int>(items.size()));
  
  // 決定ボタン
  if (ImGui::Button("SceneChange")) {

      f_ = true;
 
  }

  ImGui::End();



  if (f_) {
    // シーン切替
    if (sceneNames_[selectedIndex_] == "TitleScene") {
      g->ChangeScene(std::make_unique<TitleScene>());
      return;
    } else if (sceneNames_[selectedIndex_] == "GameScene") {
      g->ChangeScene(std::make_unique<GameScene>());
      return;
    } else if (sceneNames_[selectedIndex_] == "GameOverScene") {
      g->ChangeScene(std::make_unique<GameOverScene>());
      return;
    } else if (sceneNames_[selectedIndex_] == "GameClearScene") {
      g->ChangeScene(std::make_unique<GameClearScene>());
      return;
    } else if (sceneNames_[selectedIndex_] == "SelectScene") {
      g->ChangeScene(std::make_unique<SelectScene>());
    }
  
  }

}

void DebugSelectScene::Draw2d() {}
