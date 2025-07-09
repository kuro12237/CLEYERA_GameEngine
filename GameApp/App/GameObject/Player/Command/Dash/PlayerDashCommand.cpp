#include "PlayerDashCommand.h"
#include "../../Core/playerCore.h"


/// <summary>
/// 実行処理
/// </summary>
void PlayerDashCommand::Exec(const std::weak_ptr<PlayerCore> & player)
{
	// ダッシュ処理
	player.lock()->Dash();
}