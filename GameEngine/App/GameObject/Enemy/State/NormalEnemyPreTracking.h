#pragma once


/**
 * @file NormalEnemyTracking.h
 * @brief 通常の敵が追跡するクラス
 * @author 茂木翼
 */

#include "BaseNormalEnemyState.h"


 /// <summary>
 /// 通常の敵の追跡準備
 /// </summary>
class NormalEnemyPreTracking : public BaseNormalEnemyState {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyPreTracking();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="normalEnemy">通常の敵</param>
	void Update(NormalEnemy* normalEnemy)override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemyPreTracking() = default;


private:
	//追跡する前の方向を取得したかどうか
	bool isGetPreDirection_ = false;

};

