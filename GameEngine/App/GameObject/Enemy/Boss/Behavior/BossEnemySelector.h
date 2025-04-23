#pragma once

#include <vector>

#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 合成ノード
/// </summary>
class BossEnemySelector :BossEnemyBehaviorNode {
public:
    void AddChild(BehaviorNode * child) {
        children_.push_back(child);
    }

    NodeStatus Tick() override {
        for ( auto & child : children_ ) {
            NodeStatus status = child->Tick();
            if ( status != NodeStatus::Failure ) {
                return status;
            }
        }
        return NodeStatus::Failure;
    }


private:
    std::vector<BehaviorNode *> children_;

};