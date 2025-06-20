#pragma once

/**
 * @file BossEnemyAttack.h
 * @brief 攻撃クラス
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
    /// <param name="bulletType"></param>
    BossEnemyAttack(const uint32_t &bulletType) { this->bulletType_ = bulletType; };

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    EnemyNodeState Execute(BaseBossEnemy * baseBossEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyAttack() = default;

private:
    // 時間変化
    const float_t DELTA_TIME_ = 1.0f / 60.0f;

private:
    // 弾の種類
    uint32_t bulletType_ = 0u;
    // 生成時間
    float_t generateTime_ = 0.0f;




};

