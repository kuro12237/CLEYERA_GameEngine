#include "GameOverCamera.h"

void GameOverCamera::Init() {
  name_ = VAR_NAME(PlayerCamera);

  CameraChange();
}

void GameOverCamera::Update() {}
