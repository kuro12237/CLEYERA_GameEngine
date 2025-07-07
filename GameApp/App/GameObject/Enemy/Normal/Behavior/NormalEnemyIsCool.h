#pragma once

/**
 * @file NormalEnemyIsNotCool.h
 * @brief クールタイム中じゃないかどうかのクラス
 * @author 茂木翼
 */


#include "Enemy/Normal/Behavior/NormalEnemyBehaviorNode.h"

/// <summary>
/// クールタイム中じゃないかどうか
/// </summary>
class NormalEnemyIsNotCool : public NormalEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemyIsNotCool() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy">雑魚敵</param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseNormalEnemy *baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyIsNotCool() = default;


};