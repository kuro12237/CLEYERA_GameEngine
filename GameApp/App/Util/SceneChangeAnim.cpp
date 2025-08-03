#include "SceneChangeAnim.h"

void SceneChangeAnim::Init() {

  this->Create();
  this->GetJsonName();
  this->CreateJsonSystem("SceneChangeBack");
  uint32_t handle = texManager_->LoadPngTex("SceneChangeBackTex");
  handle_ = handle;
  anker = {};
}

void SceneChangeAnim::Update() {

  if (gameStart_) {
    time_ += 0.01f;
    if (time_ <= 1.0f) {

      color_a_ = 1.0f-this->easeInCubic(time_);

    } else {
      gameStartEnd_ = true;
      gameStart_ = false;

      time_ = 0.0f;
    }
  }

  if (gameStartEnd_ && this->isStart) {

    time_ += 0.01f;
    if (time_ <= 1.0f) {

      color_a_ = this->easeInCubic(time_);

    } else {
      isEnd_ = true;
    }
  }


  sprite_->ColorData().color_.w = color_a_;

      sprite_->Update();
  WorldMatUpdate();
}
