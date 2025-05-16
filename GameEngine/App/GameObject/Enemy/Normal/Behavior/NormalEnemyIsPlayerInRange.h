#pragma once

/**
 * @file NormalEnemyIsPlayerInRange.h
 * @brief 範囲内にいるかどうかのクラス
 * @author 茂木翼
 */


#include "Enemy/Normal/Behavior/NormalEnemyCondition.h"

/// <summary>
/// 範囲内にいるかどうか
/// </summary>
class NormalEnemyIsPlayerInRange : public NormalEnemyCondition {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="range">距離を追加</param>
    NormalEnemyIsPlayerInRange(const float_t& range){
        //範囲を設定
        this->range_ = range;
    }

    /// <summary>
    /// 状態を確認
    /// </summary>
    /// <param name="baseNormalEnemy">通常の敵</param>
    /// <returns></returns>
    bool CheckCondition(BaseNormalEnemy *baseBossEnemy) override;

private:
    //範囲
    float_t range_ = 0.0f;

};