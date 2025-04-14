#include "PlayerManager.h"

void PlayerManager::Init() {

   name_ = VAR_NAME(PlayerManager);

   //カメラ
   camera_ = std::make_shared<PlayerCamera>();
   this->cameraCompornents_.push_back(camera_);

   //コア
   core_ = std::make_shared<PlayerCore>();
   this->objComponents_.push_back(core_);

   //初期化
   this->ListInit();

   //ペアレント
   auto cameraObj = camera_->GetCamera().lock();
   auto coreObj = core_->GetGameObject().lock();

   cameraObj->SetParent(coreObj);
}

void PlayerManager::Update() {

   //更新処理
   this->ListUpdate();
}
