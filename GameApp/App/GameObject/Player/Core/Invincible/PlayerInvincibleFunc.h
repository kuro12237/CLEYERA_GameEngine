#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 前方宣言
class PlayerCore;
class PlayerCamera;

/* Playerのダッシュ処理クラス */
class PlayerInvincibleFunc {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerInvincibleFunc(PlayerCore * pPlayer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerInvincibleFunc() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

#pragma region 

	// 無敵中か
	bool IsInvincible() const {return isInvincible_;}

	// タイマー加算
	void AddInvTimer(float addTimer);

#pragma endregion 


private:

	// 親クラス
	PlayerCore * p_player_ = nullptr;

	bool isInvincible_ = false; // 無敵中か
	float invincibleTimer_ = 0.0f; // 無敵時間
};
