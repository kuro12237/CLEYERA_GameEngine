#pragma once
#include "../CLEYERA/CLEYERA.h"

class TestObject : public CLEYERA::Manager::ObjectComponent {
 public:
   TestObject() {};
   ~TestObject() {};

   void Init() override;

   void Update() override;

   void SetName(std::string name) { name_ = name; }

 private:
};
