#pragma once

/**
 * @file NormalEnemyBullet.h
 * @brief 雑魚敵の弾クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"

/// <summary>
/// 雑魚敵の弾
/// </summary>
class NormalEnemyBullet : public CLEYERA::Component::ObjectComponent {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyBullet() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemyBullet()=default;

public:
	/// <summary>
	/// 本体の座標を設定
	/// </summary>
	/// <param name="position">座標</param>
	inline void SetNormalEnemyPosition(const Math::Vector::Vec3 & position) {
		//1回だけ取得
		if ( isGetNormalEnemyPosition_ == false ) {
			this->normalEnemyPosition_ = position;
			this->isGetNormalEnemyPosition_ = true;
		}
	}

	/// <summary>
	/// プレイヤーの座標
	/// </summary>
	/// <param name="position">座標</param>
	inline void SetPlayerPosition(const Math::Vector::Vec3 & position) {
		if ( isGetPlayerPosition_ == false ) {
			this->playerPosition_ = position;
			this->isGetPlayerPosition_ = true;
		}
	}

	/// <summary>
	/// 消去されたかどうか
	/// </summary>
	/// <returns></returns>
	inline bool GetIsDelete()const {
		return isDelete_;
	}

private:
	//スケールサイズ
	const float_t SCALE_SIZE_ = 0.5f;
	//地面の高さ
	const float_t GROUND_HEIGHT_ = 0.0f;
	//FPS
    const float_t FPS_VALUE_ = 60.0f;
	//時間変化
    const float_t DELTA_TIME_ = 1.0f / FPS_VALUE_;
	//攻撃時間
    const float_t ATTACK_ALL_TIME_ = 1.0f;
	//高さ
    float_t HEIGHT_ = 4.0f;
	//消える時間
	const float_t DELETE_TIME_ = 3.0f;


private:
	// 雑魚敵本体の座標
	Math::Vector::Vec3 normalEnemyPosition_ = {};
	

	//取得し終わったかどうか
	bool isGetNormalEnemyPosition_ = false;

	//プレイヤー
	Math::Vector::Vec3 playerPosition_ = {};
	//取得し終わったかどうか
	bool isGetPlayerPosition_ = false;

	//時間
	float_t aliveTime_ = 0.0f;
	//消去されたか
	bool isDelete_ = false;

	//加速度
	float_t velocityY_ = 0.5f;
	float_t accel_ = -0.01f;

	const float_t INCREASE_T_VALUE_ = 0.01f;
	float_t t_ = 0.0f;
};

