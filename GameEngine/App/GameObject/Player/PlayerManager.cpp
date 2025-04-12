#include "PlayerManager.h"

void PlayerManager::Init() {

	name_ = VAR_NAME(PlayerManager);

   camera_ = std::make_shared<PlayerCamera>();
   this->cameraCompornents_.push_back(camera_);

   core_ = std::make_shared<PlayerCore>();
   this->objComponents_.push_back(core_);

   this->ListInit();

   auto cameraObj = camera_->GetCamera().lock();
   auto coreObj = core_->GetGameObject().lock();

   cameraObj->SetParent(coreObj);

}

void PlayerManager::Update() {

   //
   this->ListUpdate();
}
