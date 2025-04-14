#pragma once

/**
 * @file BaseNormalEnemyState.h
 * @brief 通常の敵の行動パターンの基底クラス
 * @author 茂木翼
 */

#include <memory>
#include <string>

#include "Vector3.h"


/// <summary>
/// 通常の敵
/// </summary>
class NormalEnemy;


/// <summary>
/// 通常の敵の行動パターン
/// </summary>
class BaseNormalEnemyState {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update(NormalEnemy* strongEnemy) = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseNormalEnemyState() = default;

public:

	/// <summary>
	/// 方向を取得
	/// </summary>
	/// <returns></returns>
	inline Vector3 GetDirection()const {
		return direction_;
	}

	/// <summary>
	/// X軸に方向を反転
	/// </summary>
	inline void InverseDirectionX(){
		this->direction_.x *= -1.0f;
	}

	/// <summary>
	/// Z軸に方向を反転
	/// </summary>
	inline void InverseDirectionZ() {
		this->direction_.z *= -1.0f;
	}

	/// <summary>
	/// 状態の名前を取得
	/// </summary>
	/// <returns></returns>
	std::string GetStateName()const {
		return stateName_;
	}

protected:
	//アニメーションしないようにするための時間
	const float_t NO_ANIMATION_TIME_ = 0.0f;


protected:
	//状態の名前
	std::string stateName_ = "";

	//方向
	Vector3 direction_ ={};
	//スピード
	Vector3 speed_ = {};

	

};