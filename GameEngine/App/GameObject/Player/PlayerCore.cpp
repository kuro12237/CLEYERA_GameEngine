#include "PlayerCore.h"

using namespace CLEYERA;

void PlayerCore::Init() {
   name_ = VAR_NAME(PlayerCore);

   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");

   gameObject_->ChangeModel(modelHandle);

   translate_.y = 0.0f;
   CreateCollider(ColliderType::OBB);
   this->CreateJsonSystem("Player/");

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

   if (inputManager_->PushKeyPressed(DIK_SPACE)) {

      velocity_.y += 3.0f;
   }

   TransformUpdate();
}
