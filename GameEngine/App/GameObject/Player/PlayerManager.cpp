#include "PlayerManager.h"

void PlayerManager::Init() {

   this->objComponents_.push_back(std::make_shared<PlayerCore>());

   this->ObjListInit();
}

void PlayerManager::Update() {

   //
   this->ObjListUpdate();
}
