#pragma once

/**
 * @file EnemyManager.h
 * @brief 追跡ノードクラス
 * @author 茂木翼
 */


//Actionノードについて
//このクラスのように実行するだけのクラス
//子を持つことができない

#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 追跡
/// </summary>
class BossEnemyTracking : public BossEnemyBehaviorNode {
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemyTracking() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyTracking() = default;


};
