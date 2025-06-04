#include "HealthComponent.h"

void HealthComponent::Init() {

  this->CreateJson(name_, directory_);
  hp_ = 10;

  this->SetValue(VAR_NAME(hp_), hp_);
  hp_ = this->GetValue<int32_t>(VAR_NAME(hp_));
}

void HealthComponent::ImGuiUpdate() {

  if (ImGui::TreeNode(name_.c_str())) {
    ImGui::DragInt("%d", &hp_);

    ImGui::TreePop();
  }

  JsonImGuiUpdate();
}

void HealthComponent::Update() {

  if (hp_ <= 0 && !isDead_) {
    isDead_ = true;
  }
}

void HealthComponent::CalcHp([[maybe_unused]] int32_t attackPower) {

  // 計算処理
  hp_ -= attackPower;
}
