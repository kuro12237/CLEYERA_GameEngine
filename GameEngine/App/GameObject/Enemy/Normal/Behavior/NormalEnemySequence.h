#pragma once

/**
 * @file NormalEnemySequence.h
 * @brief 雑魚敵のシーケンスノードクラス
 * @author 茂木翼
 */


#include "NormalEnemyBehaviorNode.h"

//Squenceについて
//順番に子を実行するもの
//全ての子が成功したら成功

/// <summary>
/// 雑魚敵のシーケンスノード
/// </summary>
class NormalEnemySequence :public NormalEnemyBehaviorNode {
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemySequence()=default;

    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="child"></param>
    inline void AddChild(std::unique_ptr<NormalEnemyBehaviorNode> child) {
        children_.push_back(std::move(child));
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy">雑魚敵</param>
    /// <returns></returns>
    inline EnemyNodeState Execute(BaseNormalEnemy* baseNormalEnemy)override {
        //子ノードに入っているものを全て実行していく
        for (auto & child : children_ ) {
            EnemyNodeState status = child->Execute(baseNormalEnemy);
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
    ~NormalEnemySequence()override = default;

private:
    //子ノード
    std::vector<std::unique_ptr<NormalEnemyBehaviorNode>> children_;
};