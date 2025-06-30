#include "PlayerSignatureAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerSignatureAttackCommand::Exec(const std::weak_ptr<PlayerCore> &player) {
  player.lock()->SignatureAttack();
}