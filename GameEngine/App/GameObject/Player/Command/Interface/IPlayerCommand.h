#pragma once

#include <memory>

// 前方宣言
class PlayerCore;

/* Player関連のCommandの基底クラス */
class IPlayerCommand {

public:
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IPlayerCommand() = default;

	/// <summary>
	/// 実行処理
	/// </summary>
	virtual void Exec(const std::weak_ptr<PlayerCore>& player) = 0;

	/// <summary>
	/// clone関数 : プロトタイプを複製するためのインターフェイス
	/// </summary>
	virtual std::unique_ptr<IPlayerCommand> clone() const = 0;

};
