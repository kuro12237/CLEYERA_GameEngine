#pragma once
#include "../PlayerCore.h"

#include "IPlayerState.h"

class PlayerIdleState : public IPlayerState {
 public:
   PlayerIdleState() {};
   ~PlayerIdleState() {};

   void Init() override;
   void Update() override;

 private:
};