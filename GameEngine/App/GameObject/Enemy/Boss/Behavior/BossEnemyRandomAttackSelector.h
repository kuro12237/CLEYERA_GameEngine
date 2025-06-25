#pragma once

#include "Enemy/Boss/Behavior/BossEnemySelector.h"

/// <summary>
/// ランダムで選ぶ
/// </summary>
class BossEnemyRandomAttackSelector : public BossEnemySelector {
public:
    EnemyNodeState Execute(BaseBossEnemy * baseBossEnemy) override {
        ////ランダムで攻撃選択
        //int32_t attackIndex = rand() % static_cast<int32_t >(children_.size());

        //EnemyNodeState state = children_[attackIndex]->Execute(baseBossEnemy);
        //return state;
        children_;

        // 初回または現在の子ノードが終了したらランダム選択
        if (currentChildIndex_ == -1 ||
            children_[currentChildIndex_]->Execute(baseBossEnemy) == EnemyNodeState::Success) {
            currentChildIndex_ = rand() % static_cast<int32_t>(children_.size());
        }

        return children_[currentChildIndex_]->Execute(baseBossEnemy);
    }


private:
    int currentChildIndex_ = -1; //
};
