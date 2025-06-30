#pragma once

/**
 * @file NormalEnemyIsPlayerInAttackRange.h
 * @brief 攻撃の範囲内のクラス
 * @author 茂木翼
 */


#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 攻撃の範囲内
/// </summary>
class NormalEnemyIsPlayerInAttackRange : public NormalEnemyBehaviorNode {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  NormalEnemyIsPlayerInAttackRange() = default;

  /// <summary>
  /// 実行
  /// </summary>
  /// <param name="baseNormalEnemy">雑魚敵</param>
  /// <returns></returns>
  EnemyNodeState Execute(BaseNormalEnemy *baseNormalEnemy) override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~NormalEnemyIsPlayerInAttackRange() = default;



};
