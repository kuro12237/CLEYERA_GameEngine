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


   handler_->Handler();

   handler_->Exec();

   // 更新処理
   this->ListUpdate();

   bulletManager_->Update();
}
