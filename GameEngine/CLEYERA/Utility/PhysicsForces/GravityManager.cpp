#include "GravityManager.h"

void CLEYERA::Manager::GravityManager::Init() {}

void CLEYERA::Manager::GravityManager::Update() {

   for (auto obj : objs_) {
      if (!obj.expired()) {
      }

      obj.lock()->GravityUpdate(gravity_);
   }
}

void CLEYERA::Manager::GravityManager::RemoveData() {}
