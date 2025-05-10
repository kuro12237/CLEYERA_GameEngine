#include "PlayerKeyMoveCommand.h"
#include "../../../Core/playerCore.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerKeyMoveCommand::PlayerKeyMoveCommand(const Math::Vector::Vec3 & dir)
{
	direction_ = dir;
}


/// <summary>
/// 実行処理
/// </summary>
void PlayerKeyMoveCommand::Exec(const std::weak_ptr<PlayerCore> & player)
{
	player.lock()->KeyMove(direction_);
}
