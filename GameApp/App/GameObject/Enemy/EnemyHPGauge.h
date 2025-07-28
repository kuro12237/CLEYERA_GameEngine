#pragma once

/**
 * @file EnemyHPGauge.h
 * @brief 敵の体力ゲージクラス
 * @author 茂木翼
 */

#include "CLEYERA.h"


/// <summary>
/// 敵の基底クラス
/// </summary>
class BaseEnemy;

/// <summary>
/// 敵のゲージクラス
/// </summary>
class EnemyHPGauge : public CLEYERA::Component::ObjectComponent {
public:

	EnemyHPGauge() = default;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyHPGauge(const int32_t& maxHP) {
		this->maxHP_ = maxHP;
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHPGauge() = default;

public:
	/// <summary>
	/// 敵クラスの設定
	/// </summary>
	/// <param name="baseEnemy"></param>
	inline void SetBaseEnemy(BaseEnemy * baseEnemy) {
		this->baseEnemy_ = baseEnemy;
	}

private:
	//敵
	BaseEnemy * baseEnemy_ = nullptr;
	//X座標のオフセット
	const float_t OFFSET_X_ = -2.0f;

private:
	//最大HP
	int32_t maxHP_ = 0u;

};

