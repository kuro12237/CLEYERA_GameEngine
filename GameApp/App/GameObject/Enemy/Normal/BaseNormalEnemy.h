#pragma once

/**
 * @file BaseNormalEnemy.h
 * @brief 雑魚敵の基底クラス
 * @author 茂木翼
 */

#include <Enemy/BaseEnemy.h>
#include "BaseNormalEnemyBullet.h"
#include "Enemy/Normal/Behavior/NormalEnemyBehaviorNode.h"


/// <summary>
/// 雑魚敵の基底クラス
/// </summary>
class BaseNormalEnemy : public BaseEnemy {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  BaseNormalEnemy() { hp_ = std::make_unique<HealthComponent>(); };

  /// <summary>
  /// 弾を生成
  /// </summary>
  virtual void GenerateBullet(const uint32_t & selection);

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~BaseNormalEnemy() {};

protected:
  // 弾のリスト
  std::list<std::weak_ptr<BaseNormalEnemyBullet>> bullets_;
  // ビヘイビアツリー
  std::unique_ptr<NormalEnemyBehaviorNode> behaviorTree_ = nullptr;
  

};
