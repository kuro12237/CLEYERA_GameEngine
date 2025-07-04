#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* LowAttack NormalBullet */
class LowAttack_NormalBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowAttack_NormalBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowAttack_NormalBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

#pragma region Accessor

	// 初期座標
	void SetInitPos(const Math::Vector::Vec3 & pos) { initPos_ = pos; }

	// コンボステップ
	void SetComboStep(uint32_t step) { comboStep_ = step; }

#pragma endregion

private:

	/// <summary>
	/// カーブ移動
	/// </summary>
	void CurveMove();

	/// <summary>
	/// 直線移動
	/// </summary>
	void StraightMove();

private:

	// コンボステップ
	uint32_t comboStep_ = 0;

	Math::Vector::Vec3 initPos_{};
	float elapsedTime_ = 0.0f;

	float travelDistance_ = 20.0f;    // 弾が進む最大距離
	float traveledDistance_ = 0.0f;
	float curveMagnitude_ = 5.0f;    // カーブの膨らみ具合
};
