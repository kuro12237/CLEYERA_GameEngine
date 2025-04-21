#include "PlayerMoveState.h"

void PlayerMoveState::Init() {}

void PlayerMoveState::Update() {

   if (!input_->IsLJoystickActive()) {
      core_->ChangeState(std::make_unique<PlayerIdleState>());
      return;
   }

}
