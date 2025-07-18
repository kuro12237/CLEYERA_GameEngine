#include "PlayerKeyMoveCommand.h"
#include "../../../Core/playerCore.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerKeyMoveCommand::PlayerKeyMoveCommand(const Math::Vector::Vec2 & input)
{
	keyInput_ = input;
}


/// <summary>
/// 実行処理
/// </summary>
void PlayerKeyMoveCommand::Exec(PlayerCore* ptr)
{
	ptr->KeyMove(keyInput_);
}
