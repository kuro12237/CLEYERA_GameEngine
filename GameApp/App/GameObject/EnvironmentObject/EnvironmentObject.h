#pragma once
#include"CLEYERA.h"

class EnvironmentObject:public CLEYERA::Component::ObjectComponent {
 public:
   EnvironmentObject() {};
   ~EnvironmentObject() {};

   void Init() override;

   void Update() override;

 private:
};
