#pragma once

/**
 * @file NormalEnemyIsPlayerInAttackRangeAndIsAttack.h
 * @brief 攻撃の範囲内のクラス
 * @author 茂木翼
 */


#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 攻撃の範囲内
/// </summary>
class NormalEnemyIsPlayerInAttackRangeAndIsAttack : public NormalEnemyBehaviorNode {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  NormalEnemyIsPlayerInAttackRangeAndIsAttack() = default;

  /// <summary>
  /// 実行
  /// </summary>
  /// <param name="baseNormalEnemy">雑魚敵</param>
  /// <returns></returns>
  EnemyNodeState Execute(BaseNormalEnemy *baseNormalEnemy) override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~NormalEnemyIsPlayerInAttackRangeAndIsAttack() = default;



};
