#pragma once
#include"CLEYERA.h"

class PlayerCore : public CLEYERA::Manager::ObjectComponent {
 public:
   PlayerCore() {};
   ~PlayerCore() {};

   void Init() override;

   void Update() override;

 private:
};