#pragma once

/**
 * @file BaseNormalEnemyState.h
 * @brief 通常の敵の行動パターンの基底クラス
 * @author 茂木翼
 */

#include <memory>
#include <string>



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
	/// 状態の名前を取得
	/// </summary>
	/// <returns></returns>
	std::string GetStateName()const {
		return stateName_;
	}


protected:
	//状態の名前
	std::string stateName_ = "";

	

};