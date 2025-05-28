#pragma once

/**
 * @file NormalEnemyIsNotAttacking.h
 * @brief 攻撃中じゃないかどうかのクラス
 * @author 茂木翼
 */


#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 攻撃中じゃないかどうか
/// </summary>
class NormalEnemyIsNotAttacking : public NormalEnemyBehaviorNode {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  NormalEnemyIsNotAttacking() = default;

  /// <summary>
  /// 実行
  /// </summary>
  /// <param name="baseNormalEnemy"></param>
  /// <returns></returns>
  EnemyNodeState Execute(BaseNormalEnemy *baseNormalEnemy) override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~NormalEnemyIsNotAttacking() = default;


};
