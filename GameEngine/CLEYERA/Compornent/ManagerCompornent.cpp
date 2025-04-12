#include "ManagerCompornent.h"

void CLEYERA::Component::ManagerCompornent::ObjListInit() {

   for (auto obj : objComponents_) {

      obj->Init();
   }
}

void CLEYERA::Component::ManagerCompornent::ObjListUpdate() {

   for (auto obj : objComponents_) {
      obj->Update();
   }
}