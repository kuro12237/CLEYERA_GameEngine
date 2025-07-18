#include "PlayerSignatureAttackCommand.h"
#include "../../../Core/playerCore.h"

void PlayerSignatureAttackCommand::Exec(PlayerCore * ptr) {
  ptr->SignatureAttack();
}