#include "PlayerHp.h"

void PlayerHp::Init() {

  this->CreateJson(name_, "Player");
  hp_ = 100000;

  this->SetValue(VAR_NAME(hp_), hp_);
  hp_ = this->GetValue<int32_t>(VAR_NAME(hp_));
}

void PlayerHp::ImGuiUpdate() {

  if (ImGui::TreeNode(name_.c_str())) {
    ImGui::Text("%d", hp_);

    ImGui::TreePop();
  }

  JsonImGuiUpdate();
}

void PlayerHp::CalcHp([[maybe_unused]] int32_t attackPower) {

  // 計算処理
  hp_ -= attackPower;
}
