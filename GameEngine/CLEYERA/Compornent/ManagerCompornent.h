#pragma once

#include "pch/Pch.h"

#include "../Utility/Object/ObjectCompornent.h"

namespace CLEYERA {

namespace Component {

class ManagerCompornent {
 public:
   ManagerCompornent() {};
   virtual ~ManagerCompornent() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   virtual void ImGuiUpdate() {};

#pragma region Get

   std::list<std::shared_ptr<Manager::ObjectComponent>> GetObjList() { return objComponents_; }
#pragma endregion

 private:
 protected:
   void ObjListInit();
   void ObjListUpdate();

   std::string name_ = "";

   std::list<std::shared_ptr<Manager::ObjectComponent>> objComponents_;
};

} // namespace Component

} // namespace CLEYERA
