#include "ObjectManager.h"

void CLEYERA::Manager::ObjectManager::Update() {


	for (auto object : objectList_) {
      if (object.expired()) {
         continue;
      }
      object.lock()->Update();
   }

}
