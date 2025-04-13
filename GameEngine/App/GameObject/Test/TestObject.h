#pragma once
#include"CLEYERA.h"

class TestObject : public CLEYERA::Component::ObjectComponent {
 public:
   TestObject() {};
   ~TestObject() {};

   void Init() override;

   void Update() override;


 private:
};
