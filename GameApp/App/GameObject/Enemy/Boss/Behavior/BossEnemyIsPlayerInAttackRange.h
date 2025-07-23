#pragma once

/**
 * @file BossEnemyIsPlayerInAttackRange.h
 * @brief 攻撃の範囲内のクラス
 * @author 茂木翼
 */


#include <Enemy/Boss/Behavior/BossEnemyBehaviorNode.h>

/// <summary>
/// 攻撃の範囲内
/// </summary>
class BossEnemyIsPlayerInAttackRange : public BossEnemyBehaviorNode {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
	BossEnemyIsPlayerInAttackRange() = default;

  /// <summary>
  /// 実行
  /// </summary>
  /// <param name="baseBossEnemy">雑魚敵</param>
  /// <returns></returns>
  EnemyNodeState Execute(BaseBossEnemy *baseBossEnemy) override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~BossEnemyIsPlayerInAttackRange() = default;



};
