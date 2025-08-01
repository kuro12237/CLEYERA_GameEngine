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

	/// <summary>
	/// ダッシュ処理開始
	/// </summary>
	void StartDash();

#pragma region 

	// ダッシュ中か
	bool IsDash() const {return isDashing_;}

#pragma endregion 


private:

	/// <summary>
	/// ダッシュの処理
	/// </summary>
	void Dash();


private:

	// 親クラス
	PlayerCore * p_player_ = nullptr;

	bool isDashing_ = false;
	float dashTimer_ = 0.0f;
	const float dashDuration_ = 0.1f; // ダッシュ時間（秒）
	const float dashSpeed_ = 2.0f;   // ダッシュ速度

	Math::Vector::Vec3 dashForce_ = {}; // ダッシュ速度ベクトル
};

