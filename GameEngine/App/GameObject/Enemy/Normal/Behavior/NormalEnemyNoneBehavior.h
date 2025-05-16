#pragma once

/**
 * @file BossEnemyNoneBehavior.h
 * @brief 雑魚敵1クラス
 * @author 茂木翼
 */

#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 何もしない
/// </summary>
class NormalEnemyNoneBehavior : public NormalEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemyNoneBehavior()=default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy">雑魚敵</param>
    /// <returns>状態</returns>
    EnemyNodeState Execute(BaseNormalEnemy * baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyNoneBehavior() = default;
	
};