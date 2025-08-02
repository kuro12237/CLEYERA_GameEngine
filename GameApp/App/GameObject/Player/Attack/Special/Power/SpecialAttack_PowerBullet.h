#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* SpecialAttack PowerBullet */
class SpecialAttack_PowerBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpecialAttack_PowerBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpecialAttack_PowerBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


private:

	// 爆発中フラグ初期化
	bool isExploding_ = false;

	// 爆発エフェクト用タイマー（任意で使う）
	float explodeTimer_ = 0.0f;

	Math::Vector::Vec3 initialScale_ = { 2.0f, 2.0f, 2.0f };
	Math::Vector::Vec3 explodeScaleMax_ = { 14.0f, 14.0f, 14.0f };
};