#pragma once

/**
 * @file BaseBossEnemyBullet.h
 * @brief ボスの弾クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"
#include "Enemy/EnemyParameter.h"
#include "Enemy/Boss/Behavior/BossEnemyBehaviorNode.h"


/// <summary>
/// 弾のタイプ
/// </summary>
enum BossBulletType {
  NormalBullet1,
  NormalBullet2,

};

/// <summary>
/// ボスの弾
/// </summary>
class BaseBossEnemyBullet : public CLEYERA::Component::ObjectComponent {
public:
  /// <summary>
  /// 初期化(引数が無い版)
  /// </summary>
  void Init() override {};

  /// <summary>
  /// 初期化
  /// </summary>
  virtual void Initialize(const Math::Vector::Vec3 &enemyPosition,
                          const Math::Vector::Vec3 &playerPosition) = 0;

  /// <summary>
  /// 更新
  /// </summary>
  virtual void Update() = 0;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~BaseBossEnemyBullet() = default;

public:
  /// <summary>
  /// 消去されたかどうか
  /// </summary>
  /// <returns></returns>
  inline bool GetIsDelete() const { return isDelete_; }

protected:
  // 雑魚敵本体の座標
  Math::Vector::Vec3 normalEnemyPosition_ = {};
  // プレイヤー
  Math::Vector::Vec3 playerPosition_ = {};

  // 消去されたか
  bool isDelete_ = false;
};
