#include "PlayerCommandHandler.h"
#include "../Command/Interface/IPlayerCommand.h"


/// <summary>
/// コンストラク
/// </summary>
PlayerCommandHandler::PlayerCommandHandler()
{
	// 入力
	input_ = CLEYERA::Manager::InputManager::GetInstance();
}


/// <summary>
/// 入力に基づいて実行
/// </summary>
void PlayerCommandHandler::HandleInput()
{
	// 移動処理
	if ( input_->IsLJoystickActive() ) {
		commandsMap_[ "MoveCommand" ]->Exec();
	}

	// ダッシュ
	if ( input_->PushBottonPressed(XINPUT_GAMEPAD_A) ) {
		commandsMap_[ "DashCommand" ]->Exec();
	}
}


/// <summary>
/// コマンドの設定
/// </summary>
void PlayerCommandHandler::SetCommand(const std::string & key, std::unique_ptr<IPlayerCommand> & command)
{
	commandsMap_[ key ] = std::move(command);
}

