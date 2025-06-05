#include "TestPlayGui.h"

void TestPlayGui::Init() { ManagerCompornent::name_ = VAR_NAME(TestPlayGui); }

void TestPlayGui::Update() {

  if (*enemyCount_ == 0) {
    gameState_ = GameState::Clear;
    gameStringState_ = "GameClear!!";
  }

  if (*playerHp_ <= 0) {

    gameState_ = GameState::Over;
    gameStringState_ = "GameOver!!";
  }
}

void TestPlayGui::ImGuiUpdate() {

  if (ImGui::TreeNode("TestGui")) {

    ImGui::Separator();

    std::string tag = "GameState" + gameStringState_;

    ImGui::Text(tag.c_str());
    ImGui::Text("PlayerHp::%d", *playerHp_);
    ImGui::Text("EnemyCount::%d", *enemyCount_);
    ImGui::Separator();
    if (ImGui::Button("ResetScene")) {
      resetScene_ = true;
    }
    
    ImGui::TreePop();
  };

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    for (auto obj : objComponents_) {

      obj.lock()->ImGuiUpdate();
    }
    for (auto obj : cameraCompornents_) {
      obj.lock()->ImGuiUpdate();
    }

    ImGui::TreePop();
  }
}
