#pragma once
#include <CLEYERA.h>

// 前方宣言
class PlayerCore;

/* PlayerのStateの基底クラス */
class IPlayerActionState {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IPlayerActionState() = default;

	/// <summary>
	/// 入場処理
	/// </summary>
	virtual void Enter(PlayerCore * ptr) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 入力処理
	/// </summary>
	virtual void HandleInput() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Exit() = 0;

protected:

	PlayerCore* p_Player_;
};
