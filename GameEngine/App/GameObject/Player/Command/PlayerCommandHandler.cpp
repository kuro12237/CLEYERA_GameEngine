#include "PlayerCommandHandler.h"
#include "../Command/Interface/IPlayerCommand.h"
#include "../Command/Move/PlayerMoveCommand.h"


/// <summary>
/// コンストラク
/// </summary>
PlayerCommandHandler::PlayerCommandHandler(std::weak_ptr<PlayerCore> player)
{
	// 入力デバイス
	input_ = CLEYERA::Manager::InputManager::GetInstance();

	// プレイヤーのポインタ
	player_ = player;
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerCommandHandler::Init()
{
	// 入力タイするコマンドを登録
	inputCommandMap_[ "Move" ] = []() {
		return std::make_unique<PlayerMoveCommand>();
	};
}


/// <summary>
/// 入力に基づいてコマンドを積む
/// </summary>
void PlayerCommandHandler::Handle()
{
	// 入力がアクティブなときに、コマンドを積む
	if ( input_->IsLJoystickActive() ) {
		auto it = inputCommandMap_.find("Move");
		if ( it != inputCommandMap_.end() ) {
			commands_.push(it->second());
		}
	}
}


/// <summary>
/// 実行
/// </summary>
void PlayerCommandHandler::Exec()
{
	// キュー内の全コマンドを順次実行
	while ( !commands_.empty() ) {
		auto & command = commands_.front();
		command->Exec(player_);
		commands_.pop();
	}
}
