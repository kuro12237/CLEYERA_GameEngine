#include "PlayerCamera.h"

void PlayerCamera::Init() {

   name_ = VAR_NAME(PlayerCamera);
   translate_.z = -32.0f;
   CameraChange();
}

void PlayerCamera::Update() {}
