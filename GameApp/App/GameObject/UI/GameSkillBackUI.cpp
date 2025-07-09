#include "GameSkillBackUI.h"

void GameSkillBackUI::Init() {

  this->Create();

  this->CreateJsonSystem("GamePlay");
 
  uint32_t handle = texManager_->LoadPngTex("UI/skillBack");
  handle_ = handle;
}

void GameSkillBackUI::Update() {

  sprite_->Update();
  WorldMatUpdate();
}
