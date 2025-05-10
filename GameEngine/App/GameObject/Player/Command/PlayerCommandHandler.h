#pragma once

#include "CLEYERA.h"
#include "../Command/Interface/IPlayerCommand.h"


// 前方宣言
class PlayerCore;


/* Player関連のCommandHandlerクラス */
class PlayerCommandHandler {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCommandHandler(std::weak_ptr<PlayerCore> player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCommandHandler() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 入力チェックとキューへの積み込み
	/// </summary>
	void Handle();

	/// <summary>
	/// コマンド実行
	/// </summary>
	void Exec();

private:

	/// <summary>
	/// コマンドのプッシュ
	/// </summary>
	void CommandPush(const std::string & key);

private:

	// 入力
	CLEYERA::Manager::InputManager * input_ = nullptr;

	std::queue<std::unique_ptr<IPlayerCommand>> commands_;

	// 入力->コマンド生成用のマップ
	std::unordered_map<std::string, std::function<std::unique_ptr<IPlayerCommand>()>> inputCommandMap_;

	// Playerのweak_ptr
	std::weak_ptr<PlayerCore> player_;
};