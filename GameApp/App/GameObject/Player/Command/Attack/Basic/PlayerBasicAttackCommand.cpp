#include "PlayerBasicAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerBasicAttackCommand::Exec(PlayerCore * ptr) {
  ptr->BasicAttack();
}