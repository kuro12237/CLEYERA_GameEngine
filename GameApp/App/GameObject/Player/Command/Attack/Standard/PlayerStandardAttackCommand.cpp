#include "PlayerStandardAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerStandardAttackCommand::Exec(const std::weak_ptr<PlayerCore> &player) {
  player.lock()->StandardAttack();
}
