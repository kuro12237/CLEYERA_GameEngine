#pragma once

/**
 * @file NormalEnemyTracking.h
 * @brief 追跡ノードクラス
 * @author 茂木翼
 */


//Actionノードについて
//このクラスのように実行するだけのクラス
//つまり具体的な動きをここで行う
//子を持つことができない

#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 追跡
/// </summary>
class NormalEnemyTracking : public NormalEnemyBehaviorNode {
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemyTracking()=default;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy"></param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseNormalEnemy * baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyTracking() = default;

private:
    //スピード
    const float_t SPEED_ = 0.1f;
};
