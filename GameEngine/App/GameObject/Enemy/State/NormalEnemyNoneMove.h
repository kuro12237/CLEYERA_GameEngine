#pragma once

/**
 * @file NormalEnemyNoneMove.h
 * @brief 通常の敵が動かない状態のクラス
 * @author 茂木翼
 */

#include "BaseNormalEnemyState.h"


/// <summary>
/// 通常の敵が動かない状態
/// </summary>
class NormalEnemyNoneMove : public BaseNormalEnemyState {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyNoneMove();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(NormalEnemy* normalEnemy)override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemyNoneMove()=default;
};

