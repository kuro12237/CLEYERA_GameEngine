#pragma once

#include "pch/Pch.h"

#include "../Utility/Object/ObjectCompornent.h"
#include"../Compornent/CameraCompornent.h"

namespace CLEYERA {

namespace Component {

class ManagerCompornent {
 public:
   ManagerCompornent() {};
   virtual ~ManagerCompornent() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   void ImGuiUpdate() ;

#pragma region Get

   std::list<std::shared_ptr<Manager::ObjectComponent>> GetObjList() { return objComponents_; }
#pragma endregion

 private:
 protected:
   void ListInit();
   void ListUpdate();

   std::string name_ = "";

   std::list<std::shared_ptr<Manager::ObjectComponent>> objComponents_;
   std::list<std::shared_ptr<Component::CameraCompornent>> cameraCompornents_;
};

} // namespace Component

} // namespace CLEYERA
