#include "PlayerCamera.h"

void PlayerCamera::Init() {

   name_ = VAR_NAME(PlayerCamera);
   translate_.z = -32.0f;
   CameraChange();

   CreateJsonSystem("Player/");

   this->SetImGuiFunc(std::bind(&PlayerCamera::ImGuiFunc, this));

#pragma region jsonに読み書きする変数の設定

   SetValue<Math::Vector::Vec3>("translate", translate_);
   translate_ = GetValue<Math::Vector::Vec3>("translate");

   SetValue<Math::Vector::Vec3>("rotate", rotate_);
   rotate_ = GetValue<Math::Vector::Vec3>("rotate");

   SetValue<Math::Vector::Vec3>(VAR_NAME(offset_), offset_);
   offset_ = GetValue<Math::Vector::Vec3>(VAR_NAME(offset_));

#pragma endregion
}

void PlayerCamera::Update() { translate_ = *target_ + offset_; }

void PlayerCamera::ImGuiFunc() { ImGui::DragFloat3("off", &offset_.x, 0.1f); }
