#pragma once
#include "../PlayerCore.h"

#include "IPlayerState.h"
#include"PlayerIdleState.h"

class PlayerMoveState : public IPlayerState {
 public:
   PlayerMoveState() {};
   ~PlayerMoveState() {};

   void Init() override;
   void Update() override;

 private:
};
