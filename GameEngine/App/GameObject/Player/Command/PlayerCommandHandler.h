#pragma once

#include "CLEYERA.h"


// 前方宣言
class IPlayerCommand;

/* Player関連のCommandHandlerクラス */
class PlayerCommandHandler {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCommandHandler();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCommandHandler() = default;

	/// <summary>
	/// 入力に基づいて実行
	/// </summary>
	void HandleInput();

	/// <summary>
	/// コマンドの設定
	/// </summary>
	void SetCommand(const std::string & key, std::unique_ptr<IPlayerCommand> & command);

private:

	// 入力
	CLEYERA::Manager::InputManager * input_ = nullptr;

	// CommandMap
	std::unordered_map<std::string, std::unique_ptr<IPlayerCommand>> commandsMap_;

};