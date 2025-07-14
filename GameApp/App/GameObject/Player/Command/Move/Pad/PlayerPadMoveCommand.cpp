#include "PlayerPadMoveCommand.h"
#include "../../../Core/playerCore.h"


/// <summary>
/// 実行処理
/// </summary>
void PlayerPadMoveCommand::Exec(PlayerCore* ptr)
{
	// 移動処理
	ptr->PadMove();
}

