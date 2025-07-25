#pragma once

/**
 * @file BaseBossEnemy.h
 * @brief ボスの基底クラス
 * @author 茂木翼
 */

#include "BaseBossEnemyBullet.h"
#include <Enemy/BaseEnemy.h>
#include "CLEYERA.h"
#include "Component/Hp/HealthComponent.h"
#include "Enemy/Boss/Behavior/BossEnemyBehaviorNode.h"
#include "Enemy/EnemyParameter.h"

/// <summary>
/// ボスの基底クラス
/// </summary>
class BaseBossEnemy : public BaseEnemy {
public:
  /// <summary>
  /// ベロシティの設定
  /// </summary>
  /// <param name="velocity">ベロシティ</param>
  inline void SetVelocity(const Math::Vector::Vec3 &velocity) { this->velocity_ = velocity; }

  /// <summary>
  /// 弾を生成
  /// </summary>
  virtual void GenerateBullet(const uint32_t &selection);

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~BaseBossEnemy() {};

protected:
  // ビヘイビアツリー
  std::unique_ptr<BossEnemyBehaviorNode> behaviorTree_ = nullptr;

protected:
  // 弾のリスト
  std::list<std::weak_ptr<BaseBossEnemyBullet>> bullets_;

  //発狂状態かどうか
  bool isEnraged_ = false;

  //攻撃(攻撃)
  float_t enragedAttackStartDistance_ = 2.0f;
  //追跡(発狂)
  float_t enragedTrackingStartDistance_ = 2.0f;

};
