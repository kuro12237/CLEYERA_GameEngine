#pragma once


/* Player関連のCommandの基底クラス */
class IPlayerCommand {

public:
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IPlayerCommand() = default;

	virtual void Exec(class PlayerCore & player) = 0;

};
