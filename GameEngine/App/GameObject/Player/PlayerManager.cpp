#include "PlayerManager.h"

void PlayerManager::Init() {

   name_ = VAR_NAME(PlayerManager);

   // カメラ
   camera_ = std::make_shared<PlayerCamera>();
   this->cameraCompornents_.push_back(camera_);

   // コア
   core_ = std::make_shared<PlayerCore>();
   this->objComponents_.push_back(core_);

   // 弾管理クラス
   bulletManager_ = std::make_shared<PlayerBulletManager>();
   bulletManager_->Init();

   handler_ = std::make_unique<PlayerCommandHandler>();
   handler_->SetPlayer(core_);
   handler_->SetPlayer(bulletManager_);
   handler_->Init();

   // 初期化
   this->ListInit();

   // ペアレント
   camera_->SetTarget(core_->GetTranslate());
}

void PlayerManager::Update() {

    Math::Vector::Vec3 direction = {}; // 入力方向ベクトル

    float baseSpeed = 0.1f;
    if ( inputManager_->PushKey(DIK_LSHIFT) ) {
        baseSpeed *= 5.0f;
    }
    // 入力方向をベクトルで表現
    if ( inputManager_->PushKey(DIK_W) )
        direction.z += 1.0f;
    if ( inputManager_->PushKey(DIK_S) )
        direction.z -= 1.0f;
    if ( inputManager_->PushKey(DIK_D) )
        direction.x += 1.0f;
    if ( inputManager_->PushKey(DIK_A) )
        direction.x -= 1.0f;

    // 正規化（斜め移動を速くしすぎないように）
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if ( len > 0.0f ) {
        direction.x /= len;
        direction.y /= len;
        direction.z /= len;
    }
    force_.x = direction.x * baseSpeed;
    force_.z = direction.z * baseSpeed;

    if ( inputManager_->PushKeyPressed(DIK_SPACE) ) {

        velocity_.y += 3.0f;
    }


   handler_->Handler();

   handler_->Exec();

   // 更新処理
   this->ListUpdate();

   bulletManager_->Update();
}
