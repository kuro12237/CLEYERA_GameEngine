#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 前方宣言
class PlayerCore;
class PlayerCamera;

/* Playerのダッシュ処理クラス */
class PlayerDashFunc {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerDashFunc(PlayerCore* pPlayer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerDashFunc() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	// 親クラス
	PlayerCore * p_player_ = nullptr;


};

