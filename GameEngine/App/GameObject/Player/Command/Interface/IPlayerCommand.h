#pragma once


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
	virtual void Exec() = 0;

};
