#pragma once


/**
 * @file BossEnemyMagicAttack.h
 * @brief 魔法攻撃クラス
 * @author 茂木翼
 */


 //Actionノードについて
 //このクラスのように実行するだけのクラス
 //つまり具体的な動きをここで行う
 //子を持つことができない

#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 魔法攻撃
/// </summary>
class BossEnemyMagicAttack : public BossEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemyMagicAttack() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyMagicAttack()override = default;


};

