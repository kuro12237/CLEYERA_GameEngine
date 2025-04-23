#pragma once

/**
 * @file BossEnemySequence.h
 * @brief ボスのシーケンスノードクラス
 * @author 茂木翼
 */


#include "BossEnemyBehaviorNode.h"

/// <summary>
/// ボスのシーケンスノード
/// </summary>
class BossEnemySequence :BossEnemyBehaviorNode {
public:
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="child"></param>
    void AddChild(BossEnemyBehaviorNode * child) {
        children_.push_back(child);
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <returns></returns>
    NodeState Tick() override {
        for ( auto & child : children_ ) {
            NodeState status = child->Tick();
            if ( status != NodeState::Success ) {
                return status;
            }
        }
        return NodeState::Success;
    }

private:
    //子ノード
    std::vector<BossEnemyBehaviorNode *> children_;
};