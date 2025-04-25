#pragma once

#include "BossEnemyBehaviorNode.h"

class BossEnemyCondition : public BossEnemyBehaviorNode {
public:
    /// <summary>
    /// 状態を確認
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    virtual bool CheckCondition(BaseBossEnemy * baseBossEnemy) = 0;

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    inline NodeState Execute(BaseBossEnemy * baseBossEnemy) override {

        //trueだった場合成功
        if ( CheckCondition(baseBossEnemy) ) {
            return NodeState::Success;
        }
        else {
            return NodeState::Failure;
        }
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyCondition()override = default;

};