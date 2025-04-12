#include "ManagerCompornent.h"

void CLEYERA::Component::ManagerCompornent::ImGuiUpdate() {

   if (name_ == "") {
      return;
   }

   if (ImGui::TreeNode(name_.c_str())) {

      for (auto obj : objComponents_) {

         obj->ImGuiUpdate();
      }
      for (auto obj : cameraCompornents_) {
         obj->ImGuiUpdate();
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Component::ManagerCompornent::ListInit() {

   for (auto obj : objComponents_) {

      obj->Init();
   }
   for (auto obj : cameraCompornents_) {
      obj->Init();
   }
}

void CLEYERA::Component::ManagerCompornent::ListUpdate() {

   for (auto obj : objComponents_) {
      obj->Update();
   }
   for (auto obj : cameraCompornents_) {
      obj->Update();
   }
}