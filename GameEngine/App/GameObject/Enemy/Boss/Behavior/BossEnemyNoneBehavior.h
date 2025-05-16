#pragma once

#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 何もしない
/// </summary>
class BossEnemyNoneBehavior : public BossEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemyNoneBehavior()=default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    EnemyNodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyNoneBehavior() = default;
	
};