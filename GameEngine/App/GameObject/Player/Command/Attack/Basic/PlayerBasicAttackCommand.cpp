#include "PlayerBasicAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerBasicAttackCommand::Exec(const std::weak_ptr<PlayerCore> &player) {
  player.lock()->BasicAttack();
}