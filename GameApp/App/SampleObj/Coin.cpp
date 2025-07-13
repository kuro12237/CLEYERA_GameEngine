#include "Coin.h"

void Coin::Init() {
  this->Create();
  scale_ = {0.1f, 0.1f, 0.1f};
}

void Coin::Update() {

  this->WorldMatUpdate();

  sprite_->Update();
}
