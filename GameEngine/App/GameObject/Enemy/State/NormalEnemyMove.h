#pragma once

/**
 * @file NormalEnemyMove.h
 * @brief 通常の敵が動かない状態のクラス
 * @author 茂木翼
 */

#include "BaseNormalEnemyState.h"

/// <summary>
/// 通常の敵が動く状態
/// </summary>
class NormalEnemyMove : public BaseNormalEnemyState {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyMove();

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
	~NormalEnemyMove()=default;

private:
	//スピードの値
	float speedAmount_ = 0.01f;

};

