#pragma once

/**
 * @file BossEnemySequence.h
 * @brief ボスのシーケンスノードクラス
 * @author 茂木翼
 */


#include "BossEnemyBehaviorNode.h"


//Squenceについて
//順番に子を実行するもの

/// <summary>
/// ボスのシーケンスノード
/// </summary>
class BossEnemySequence :BossEnemyBehaviorNode {
public:
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="child"></param>
    void AddChild(std::unique_ptr<BossEnemyBehaviorNode> child) {
        children_.push_back(child);
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    NodeState Execute(std::unique_ptr<BaseBossEnemy> baseBossEnemy) override {
        for (auto & child : children_ ) {
            NodeState status = child->Execute(std::move(baseBossEnemy));
            if ( status != NodeState::Success ) {
                return status;
            }
        }
        return NodeState::Success;
    }

private:
    //子ノード
    std::vector<std::unique_ptr<BossEnemyBehaviorNode>> children_;
};