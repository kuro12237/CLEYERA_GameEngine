#pragma once

#include "LowAttack_BackBullet.h"
#include "../../Interface/IMagicAttack.h"
#include <CLEYERA.h>


/* LowAttack Back */
class LowAttack_Back : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowAttack_Back() = default;
	LowAttack_Back(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr, std::weak_ptr<EnemyManager> EneManaPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowAttack_Back() = default;

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
	/// ベクトルvを、axis軸を中心にangle[ラジアン]回転
	/// </summary>
	Math::Vector::Vec3 RotateAroundAxis(const Math::Vector::Vec3 & v, const Math::Vector::Vec3 & axisRaw, float angle);

	/// <summary>
	/// 
	/// </summary>
	float DegreesToRadians(float deg);


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