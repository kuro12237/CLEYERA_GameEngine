#include "InputManager.h"

void CLEYERA::Manager::InputManager::Init() {
   keyBord_ = std::make_unique<Util::InputKeyBord>();

   keyBord_ = std::make_unique<Util::InputKeyBord>();
   keyBord_->Init();
}

void CLEYERA::Manager::InputManager::Finalize() { keyBord_.reset(); }

void CLEYERA::Manager::InputManager::Begin() { keyBord_->Begin(); }
