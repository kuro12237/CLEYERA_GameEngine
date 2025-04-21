#pragma once

/**
 * @file NormalEnemyTracking.h
 * @brief 通常の敵が追跡するクラス
 * @author 茂木翼
 */

#include "BaseNormalEnemyState.h"


/// <summary>
/// 通常の敵が追跡する
/// </summary>
class NormalEnemyTracking : public BaseNormalEnemyState {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyTracking();

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
	~NormalEnemyTracking()=default;
};

