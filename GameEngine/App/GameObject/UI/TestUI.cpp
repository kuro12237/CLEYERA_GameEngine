#include "TestUI.h"

void TestUI::Init() { this->Create(); }

void TestUI::Update() {

  this->sprite_->LayerChange(3);

  this->sprite_->LayerChange(0);

  this->sprite_->Update();
}
