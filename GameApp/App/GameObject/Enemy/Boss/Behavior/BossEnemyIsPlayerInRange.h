#pragma once


#include "Enemy/Boss/BossEnemyCondition.h"

/// <summary>
/// 範囲内にいるかどうか
/// </summary>
class BossEnemyIsPlayerInRange : public BossEnemyCondition {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="range">距離を追加</param>
    BossEnemyIsPlayerInRange(const float_t& range){
        //範囲を設定
        this->range_ = range;
    }

    /// <summary>
    /// 状態を確認
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    bool CheckCondition(BaseBossEnemy * baseBossEnemy) override;

private:
    //範囲
    float_t range_;

    
};