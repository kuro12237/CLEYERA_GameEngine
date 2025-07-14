#include "PlayerStandardAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerStandardAttackCommand::Exec(PlayerCore* ptr) {
  ptr->StandardAttack();
}
