#include "PlayerCore.h"

using namespace CLEYERA;

void PlayerCore::Init() {
   // 基本クラス名をマクロ通して入れる
   name_ = VAR_NAME(PlayerCore);

   // modelの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
   gameObject_->ChangeModel(modelHandle);

   /// コライダー作成:現状OBB飲み
   CreateCollider(ColliderType::OBB);

   // jsonのファイル作成
   this->CreateJsonSystem("Player/");

   // jsonに読み書きする変数の設定
   SetValue<Math::Vector::Vec3>("t", translate_);
   translate_ = GetValue<Math::Vector::Vec3>("t");
}

void PlayerCore::Update() {

   Math::Vector::Vec3 direction = {}; // 入力方向ベクトル

   float baseSpeed = 0.1f;
   if (inputManager_->PushKey(DIK_LSHIFT)) {
      baseSpeed *= 5.0f;
   }

   // 入力方向をベクトルで表現
   if (inputManager_->PushKey(DIK_W))
      direction.z += 1.0f;
   if (inputManager_->PushKey(DIK_S))
      direction.z -= 1.0f;
   if (inputManager_->PushKey(DIK_D))
      direction.x += 1.0f;
   if (inputManager_->PushKey(DIK_A))
      direction.x -= 1.0f;

   // 正規化（斜め移動を速くしすぎないように）
   float len = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
   if (len > 0.0f) {
      direction.x /= len;
      direction.y /= len;
      direction.z /= len;
   }
   force_.x = direction.x * baseSpeed;
   force_.z = direction.z * baseSpeed;

   Math::Vector::Vec2 joyR = inputManager_->JoyLPos();
   force_.x = joyR.x;
   force_.z = joyR.y;

   if (inputManager_->PushKeyPressed(DIK_SPACE)) {

      velocity_.y += 3.0f;
   }

   if (inputManager_->PushBottonPressed(XINPUT_GAMEPAD_A)) {

      velocity_.y += 3.0f;
   }

   if (inputManager_->IsLeftTriggerPressed()) {
      rotate_.y += 0.02f;
   }
   if (inputManager_->IsRightTriggerPressed()) {
      rotate_.y -= 0.02f;
   }
   TransformUpdate();
}
