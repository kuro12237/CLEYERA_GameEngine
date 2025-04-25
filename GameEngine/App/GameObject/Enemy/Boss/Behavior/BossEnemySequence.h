#pragma once

/**
 * @file BossEnemySequence.h
 * @brief ボスのシーケンスノードクラス
 * @author 茂木翼
 */


#include "BossEnemyBehaviorNode.h"


//Squenceについて
//順番に子を実行するもの
//全ての子が成功したら成功

/// <summary>
/// ボスのシーケンスノード
/// </summary>
class BossEnemySequence :public BossEnemyBehaviorNode {
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemySequence();

    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="child"></param>
    inline void AddChild(std::unique_ptr<BossEnemyBehaviorNode> child) {
        children_.push_back(std::move(child));
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    inline NodeState Execute(BaseBossEnemy* baseBossEnemy)override {
        //子ノードに入っているものを全て実行していく
        for (auto & child : children_ ) {
            NodeState status = child->Execute(baseBossEnemy);
            //成功でなくなったら状態を返す
            if ( status != NodeState::Success ) {
                return status;
            }
        }
        return NodeState::Success;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemySequence()override = default;

private:
    //子ノード
    std::vector<std::unique_ptr<BossEnemyBehaviorNode>> children_;
};