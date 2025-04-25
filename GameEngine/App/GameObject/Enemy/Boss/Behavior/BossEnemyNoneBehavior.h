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
    BossEnemyNoneBehavior();

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyNoneBehavior() = default;
	
};