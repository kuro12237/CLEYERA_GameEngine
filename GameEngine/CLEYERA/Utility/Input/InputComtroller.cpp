#include "InputComtroller.h"

void CLEYERA::Util::InputController::Init() {}

void CLEYERA::Util::InputController::Begin() {

   preJoyState_ = joyState_;
   XInputGetState(0, &joyState_);
}

Math::Vector::Vec2 CLEYERA::Util::InputController::GetJoyLStickPos(const float &mode) {

   float deadzone = 0.01f;

   Math::Vector::Vec2 joyPos(joyState_.Gamepad.sThumbLX / mode, joyState_.Gamepad.sThumbLY / mode);

   if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone) {
      return joyPos;
   }
   return {};
}

Math::Vector::Vec2 CLEYERA::Util::InputController::GetJoyRStickPos(const float &mode) {

   float deadzone = 0.01f;
   Math::Vector::Vec2 joyPos(joyState_.Gamepad.sThumbRX / mode, joyState_.Gamepad.sThumbRY / mode);

   if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone) {
      return joyPos;
   }

   return {};
}
