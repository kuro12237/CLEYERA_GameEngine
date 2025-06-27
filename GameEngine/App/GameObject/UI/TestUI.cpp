#include "TestUI.h"

void TestUI::Init() {
  this->Create();

  handle_ = texManager_->LoadPngTex("uvChecker");
}

void TestUI::Update() {

  this->sprite_->LayerChange(3);

  this->sprite_->LayerChange(0);

  this->sprite_->Update();
  this->WorldMatUpdate();
}
