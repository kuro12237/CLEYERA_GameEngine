#pragma once
#include "CLEYERA.h"
#include "IPlayerBullet.h"

class PlayerBullet : public IPlayerBullet {
 public:
   PlayerBullet() {};
   ~PlayerBullet() {};

   void Init() override;

   void Update() override;

 
 private:

};
