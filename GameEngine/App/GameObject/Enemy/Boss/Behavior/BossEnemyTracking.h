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
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Execute(std::unique_ptr<BaseBossEnemy> baseBossEnemy) override {

        return NodeState::Success;
    }

};
