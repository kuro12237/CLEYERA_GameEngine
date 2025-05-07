#pragma once

#include "Enemy/Boss/Behavior/BossEnemySelector.h"

/// <summary>
/// ランダムで選ぶ
/// </summary>
class BossEnemyRandomAttackSelector : public BossEnemySelector {
public:
    NodeState Execute(BaseBossEnemy * baseBossEnemy) override {
        //ランダムで攻撃選択
        int32_t attackIndex = rand() % static_cast<int32_t >(children_.size());

        NodeState state = children_[attackIndex]->Execute(baseBossEnemy);
        return state;
    }
};
