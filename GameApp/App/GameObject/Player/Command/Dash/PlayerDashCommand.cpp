#include "PlayerDashCommand.h"
#include "../../Core/playerCore.h"


/// <summary>
/// 実行処理
/// </summary>
void PlayerDashCommand::Exec(PlayerCore* ptr)
{
	// ダッシュ処理
	ptr->Dash();
}