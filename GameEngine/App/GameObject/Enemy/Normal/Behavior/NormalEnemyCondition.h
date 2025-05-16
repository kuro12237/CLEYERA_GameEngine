#pragma once

/**
 * @file NormalEnemyCondition.h
 * @brief 雑魚敵の状態クラス
 * @author 茂木翼
 */

#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 雑魚敵の状態
/// </summary>
class NormalEnemyCondition : public NormalEnemyBehaviorNode {
public:
  /// <summary>
  /// 状態を確認
  /// </summary>
  /// <param name="baseBossEnemy"></param>
  /// <returns></returns>
  virtual bool CheckCondition(BaseNormalEnemy *baseBossEnemy) = 0;

  /// <summary>
  /// 実行
  /// </summary>
  /// <param name="baseBossEnemy"></param>
  /// <returns></returns>
  inline EnemyNodeState Execute(BaseNormalEnemy *baseBossEnemy) override {

    // trueだった場合成功
    if (CheckCondition(baseBossEnemy) == true) {
      return EnemyNodeState::Success;
    } else {
      return EnemyNodeState::Failure;
    }
  }

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~NormalEnemyCondition() override = default;
};