#include "GameLowAttackUI.h"

void GameLowAttackUI::Init() {
  this->Create();
  this->GetJsonName();
  this->CreateJsonSystem("GamePlay");
  uint32_t handle = texManager_->LoadPngTex("UI/Low_Attack_Normal");
  handle_ = handle;
}

void GameLowAttackUI::Update() {

  sprite_->Update();
  WorldMatUpdate();
}
