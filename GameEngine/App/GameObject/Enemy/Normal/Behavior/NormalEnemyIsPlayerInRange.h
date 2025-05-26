#pragma once

/**
 * @file NormalEnemyIsPlayerInRange.h
 * @brief 範囲内にいるかどうかのクラス
 * @author 茂木翼
 */


#include "Enemy/Normal/Behavior/NormalEnemyBehaviorNode.h"

/// <summary>
/// 範囲内にいるかどうか
/// </summary>
class NormalEnemyIsPlayerInRange : public NormalEnemyBehaviorNode {
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
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy">雑魚敵</param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseNormalEnemy *baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyIsPlayerInRange() = default;

  private:
    //範囲
    float_t range_ = 0.0f;

};