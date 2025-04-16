#include "PlayerCamera.h"

void PlayerCamera::Init() {

   name_ = VAR_NAME(PlayerCamera);
   translate_.z = -32.0f;
   CameraChange();

   CreateJsonSystem("Player/");

#pragma region jsonに読み書きする変数の設定

   SetValue<Math::Vector::Vec3>("translate", translate_);
   translate_ = GetValue<Math::Vector::Vec3>("translate");

   
   SetValue<Math::Vector::Vec3>("rotate", rotate_);
   rotate_ = GetValue<Math::Vector::Vec3>("rotate");

#pragma endregion
}

void PlayerCamera::Update() {}
