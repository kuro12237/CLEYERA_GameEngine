#include "TitleCamera.h"

void TitleCamera::Init() {
  name_ = VAR_NAME(PlayerCamera);

  translate_.y = 3.5f;
  CameraChange();
}

void TitleCamera::Update() {}
