#pragma once

/**
 * @file NormalEnemyAttack.h
 * @brief 攻撃ノードクラス
 * @author 茂木翼
 */


 //Actionノードについて
 //このクラスのように実行するだけのクラス
 //つまり具体的な動きをここで行う
 //子を持つことができない

#include "NormalEnemyCondition.h"

/// <summary>
/// 攻撃
/// </summary>
class NormalEnemyAttack : public NormalEnemyCondition {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemyAttack() = default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseNormalEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyAttack() = default;
};

