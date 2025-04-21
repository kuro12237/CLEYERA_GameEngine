#include "PlayerCamera.h"

void PlayerCamera::Init() {

   name_ = VAR_NAME(PlayerCamera);
   //回転
   rotate_.x = 0.5f;

   //座標
   translate_.z = -32.0f;
   translate_.y = 23.0f;
   CameraChange();
}

void PlayerCamera::Update() {



}
