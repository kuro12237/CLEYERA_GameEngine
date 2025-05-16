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
    BossEnemySequence()=default;

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
    inline EnemyNodeState Execute(BaseBossEnemy* baseBossEnemy)override {
        //子ノードに入っているものを全て実行していく
        for (auto & child : children_ ) {
            EnemyNodeState status = child->Execute(baseBossEnemy);
            //成功でなくなったら状態を返す
            if ( status != EnemyNodeState::Success ) {
                return status;
            }
        }
        return EnemyNodeState::Success;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemySequence()override = default;

private:
    //子ノード
    std::vector<std::unique_ptr<BossEnemyBehaviorNode>> children_;
};