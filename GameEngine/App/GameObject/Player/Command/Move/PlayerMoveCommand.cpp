#include "PlayerMoveCommand.h"
#include "../../Core/playerCore.h"


/// <summary>
/// 実行処理
/// </summary>
void PlayerMoveCommand::Exec(const std::weak_ptr<PlayerCore> & player)
{
	player.lock()->Move();
}
