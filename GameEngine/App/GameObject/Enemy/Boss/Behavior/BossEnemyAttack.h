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
/// 攻撃
/// </summary>
class BossEnemyAttack : public BossEnemyBehaviorNode{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemyAttack() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyAttack() = default;



private:

};

