#pragma once

#include "LowAttack_NormalBullet.h"
#include "../../Interface/IMagicAttack.h"
#include <CLEYERA.h>


/* LowAttack Normal */
class LowAttack_Normal : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowAttack_Normal() = default;
	LowAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowAttack_Normal() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// リセット
	/// </summary>
	void Reset() override;

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void IsAttack() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrwaImGui() override;

private:

	/// <summary>
	/// 射撃処理
	/// </summary>
	void FireBullet();


private:

	// スクリプト
	std::unique_ptr<LuaScript> lua_;

	// コンボの最大値
	uint32_t comboMax_ = 0;
	// 射撃ステップ
	uint32_t comboStep_ = 0;
	// コンボ間のインターバル
	float comboInterval_ = 0.0f;
	// コンボ進行タイマー
	float comboElapse_ = 0.0f;
};
