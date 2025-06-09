#include "ManagerCompornent.h"

void CLEYERA::Component::ManagerCompornent::ImGuiUpdate() {

   if (name_ == "") {
      return;
   }

   if (ImGui::TreeNode(name_.c_str())) {

      for (auto obj : objComponents_) {

         obj.lock()->ImGuiUpdate();
      }
      for (auto obj : cameraCompornents_) {
        obj.lock()->ImGuiUpdate();
      }

      ImGui::TreePop();
   }
}

void CLEYERA::Component::ManagerCompornent::ListInit() {

   for (auto obj : objComponents_) {

      obj.lock()->Init();
   }
   for (auto obj : cameraCompornents_) {
      obj.lock()->Init();
   }
}

void CLEYERA::Component::ManagerCompornent::ListUpdate() {

   for (auto obj : objComponents_) {
    obj;
    //obj.lock()->Update();
   }
   for (auto obj : cameraCompornents_) {
      obj.lock()->Update();
   }
}