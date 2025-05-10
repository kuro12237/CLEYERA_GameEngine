#include "PlayerPadMoveCommand.h"
#include "../../../Core/playerCore.h"


/// <summary>
/// 実行処理
/// </summary>
void PlayerPadMoveCommand::Exec(const std::weak_ptr<PlayerCore> & player)
{
	// 移動処理
	player.lock()->PadMove();
	// 移動方向に体の向きを合わせる
	player.lock()->CalcBodyOrienation();
}

