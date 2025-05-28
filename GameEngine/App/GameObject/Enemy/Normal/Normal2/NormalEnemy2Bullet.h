#pragma once

/**
 * @file NormalEnemy2Bullet.h
 * @brief 雑魚敵の弾クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"

/// <summary>
/// 雑魚敵の弾
/// </summary>
class NormalEnemy2Bullet : public CLEYERA::Component::ObjectComponent {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
  NormalEnemy2Bullet() = default;

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
    ~NormalEnemy2Bullet() = default;

private:
    /// <summary>
    /// ImGui表示用
    /// </summary>
    void DisplayImGui();

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
	const float_t SCALE_SIZE_ = 1.0f;
	//弾の速さ
    const float_t SPEED_ = 0.1f;
	//時間変化
    const float_t DELTA_TIME_ = 1.0f/60.0f;
	//最大表示時間
    const float_t MAX_DISPLAY_TIME_ = 5.0f;

private:
	// 雑魚敵本体の座標
	Math::Vector::Vec3 normalEnemyPosition_ = {};
	//取得し終わったかどうか
	bool isGetNormalEnemyPosition_ = false;

	//プレイヤー
	Math::Vector::Vec3 playerPosition_ = {};
	//取得し終わったかどうか
	bool isGetPlayerPosition_ = false;


	//方向
    Math::Vector::Vec3 direction_ = {};

	// 表示時間
    float_t displayTime_ = 0.0f;
	//決めたかどうか
    bool isDelete_ = false;

};

