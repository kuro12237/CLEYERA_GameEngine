#pragma once


/**
 * @file EnemyManager.h
 * @brief ボスの合成ノードクラス
 * @author 茂木翼
 */

//Selector
//成功する子が見つかるまで1つ1つ実行する


#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 合成ノード
/// </summary>
class BossEnemySelector :BossEnemyBehaviorNode {
public:
    /// <summary>
    /// 子を追加
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
        for ( auto & child : children_ ) {
            NodeState status = child->Execute(std::move(baseBossEnemy));
            if ( status != NodeState::Failure ) {
                return status;
            }
        }
        return NodeState::Failure;
    }


private:
    //子ノード
    std::vector<std::unique_ptr<BossEnemyBehaviorNode>> children_;

};