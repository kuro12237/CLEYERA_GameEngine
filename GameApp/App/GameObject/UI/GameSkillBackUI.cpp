#include "GameSkillBackUI.h"

void GameSkillBackUI::Init() {

  this->Create();

  this->CreateJsonSystem("GamePlay");

  uint32_t handle = texManager_->LoadPngTex("UI/skillBack");
  handle_ = handle;
}

void GameSkillBackUI::Update() {

  if (ImGui::TreeNode(name_.c_str())) {

    ImGui::DragFloat4("color", &sprite_->ColorData().color_.x, 0.01f);
    ImGui::TreePop();
  }
  sprite_->Update();
  WorldMatUpdate();
}
