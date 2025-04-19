#include "ObjectManager.h"

void CLEYERA::Manager::ObjectManager::Update() {


   for (auto it = objectList_.begin(); it != objectList_.end();) {

      if (!(*it).expired()) {

         (*it).lock()->Update();
         ++it;
      } else {
         it = objectList_.erase(it);
      }
   }
}

void CLEYERA::Manager::ObjectManager::ImGuiUpdate() {

    for (auto it = objectList_.begin(); it != objectList_.end();) {

      if (!(*it).expired()) {

         (*it).lock()->ImGuiUpdate();
         ++it;
      } else {
         it = objectList_.erase(it);
      }
   }
}
