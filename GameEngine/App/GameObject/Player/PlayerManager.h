#pragma once
#include"CLEYERA.h"
#include"PlayerCore.h"

class PlayerManager:public CLEYERA::Component::ManagerCompornent {
 public:
   PlayerManager() {};
   ~PlayerManager() {};

   void Init()override;

   void Update()override;


 private:
};
