#pragma once

#include "BossEnemyCondition.h"

/// <summary>
/// 発狂状態かどうか
/// </summary>
class BossEnemyIsEnraged :public BossEnemyCondition {
public:
	/// <summary>
	/// 状態を確認
	/// </summary>
	/// <param name="baseBossEnemy"></param>
	/// <returns></returns>
	bool CheckCondition(BaseBossEnemy * baseBossEnemy)override;


};