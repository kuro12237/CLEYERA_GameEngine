#pragma once

/**
 * @file EnemyManager.h
 * @brief 追跡ノードクラス
 * @author 茂木翼
 */

//Actionノードについて
//このクラスのように実行するだけのクラス
//つまり具体的な動きをここで行う
//子を持つことができない

#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 突進攻撃
/// </summary>
class BossEnemyThrustAttack : public BossEnemyBehaviorNode {
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemyThrustAttack() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyThrustAttack()override = default;


};