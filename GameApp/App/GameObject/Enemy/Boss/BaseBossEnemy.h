#pragma once

/**
 * @file BaseBossEnemy.h
 * @brief ボスの基底クラス
 * @author 茂木翼
 */

#include "BaseBossEnemyBullet.h"
#include "CLEYERA.h"
#include "Component/Hp/HealthComponent.h"
#include "Enemy/Boss/Behavior/BossEnemyBehaviorNode.h"
#include "Enemy/EnemyParameter.h"

/// <summary>
/// ボスの基底クラス
/// </summary>
class BaseBossEnemy : public CLEYERA::Component::ObjectComponent {
protected:
  /// <summary>
  /// ノックバック
  /// </summary>
  virtual void KnockBack() = 0;

  /// <summary>
  /// 倒された
  /// </summary>
  virtual void Killed() = 0;

public:
  /// <summary>
  /// プレイヤーの座標
  /// </summary>
  /// <param name="position">座標</param>
  inline void SetPlayerPosition(const Math::Vector::Vec3 &position) {
    this->playerPosition_ = position;
  }

  /// <summary>
  /// 生成時の初期座標
  /// </summary>
  /// <param name="position">座標</param>
  inline void SetInitialPosition(const Math::Vector::Vec3 &position) {
    this->translate_ = position;
  }
  /// <summary>
  /// ベロシティの設定
  /// </summary>
  /// <param name="velocity">ベロシティ</param>
  inline void SetVelocity(const Math::Vector::Vec3 &velocity) { this->velocity_ = velocity; }

  /// <summary>
  /// 方向を設定
  /// </summary>
  /// <param name="direction"></param>
  inline void SetDirection(const Math::Vector::Vec3 & direction) { this->direction_ = direction; }

  /// <summary>
  /// 座標の取得
  /// </summary>
  /// <returns>座標</returns>
  inline Math::Vector::Vec3 GetPosition() const { return translate_; }

  /// <summary>
  /// プレイヤーの座標を取得
  /// </summary>
  /// <returns>座標</returns>
  inline Math::Vector::Vec3 GetPlayerPosition() const { return playerPosition_; }

  /// <summary>
  /// パラメーターを取得
  /// </summary>
  /// <returns></returns>
  inline EnemyParameter GetBossEnemyParameter() const { return parameter_; }

  /// <summary>
  /// 攻撃をしているかを取得
  /// </summary>
  /// <returns></returns>
  inline bool GetIsAttack() const { return isAttack_; }

  /// <summary>
  /// 攻撃のフラグを設定
  /// </summary>
  /// <param name="isAttack"></param>
  inline void SetIsAttack(const bool &isAttack) { this->isAttack_ = isAttack; }

  /// <summary>
  /// 消えているかどうかを取得
  /// </summary>
  inline bool GetIsDelete() const { return isDelete_; }

  /// <summary>
  /// 消す
  /// </summary>
  inline void SetDelete() { this->isAlive_ = false; }

  /// <summary>
  /// 弾を生成
  /// </summary>
  virtual void GenerateBullet(const uint32_t &selection);

  /// <summary>
  /// 攻撃開始距離を取得
  /// </summary>
  /// <returns></returns>
  float_t GetAttackStartDistance() const { return attackStartDistance_; }


  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~BaseBossEnemy() {};

protected:
  // プレイヤー座標
  Math::Vector::Vec3 playerPosition_ = {};
  // 方向
  Math::Vector::Vec3 direction_ = {};
  // プレイヤーへの方向
  Math::Vector::Vec3 directionToPlayer_ = {};
  // ビヘイビアツリー
  std::unique_ptr<BossEnemyBehaviorNode> behaviorTree_ = nullptr;

  // 生存かどうか
  bool isAlive_ = true;
  // 消えるかどうか
  bool isDelete_ = false;

  //クールタイム中かどうか
  bool isCool_ = false;
  //時間
  float_t coolTime_ = 0.0f;
  //制限
  float_t coolTimeLimit_ = 3.0f;
  //生成した弾の数。これが無いと管理しにくい
  uint32_t generateBulletNumber_ = 0u;

  // 攻撃したかどうか
  bool isAttack_ = false;

  // ノックバック
  bool isKnockBack_ = false;
  // 時間
  float_t knockBackTime_ = 0.0f;
  // 線形補間
  float_t knockbackT_ = 0.0f;
  // 方向を決める
  bool isDesidePosition_ = false;

  // ノックバック前の座標
  Math::Vector::Vec3 beforeKnockBackPosition_ = {};
  // ノックバック後の座標
  Math::Vector::Vec3 afterKnockBackPosition_ = {};

protected:
  // 最大ノックバック時間
  const float_t MAX_KNOCK_BACK_TIME_ = 3.0f;
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / 60.0f;
  // 線形補間
  const float_t INCREASE_T_VALUE_ = 0.1f;

protected:
  // 弾のリスト
  std::list<std::weak_ptr<BaseBossEnemyBullet>> bullets_;
  //カウント
  int32_t bulletCount_ = 0;

  // パラメーター
  EnemyParameter parameter_ = {};
  // 攻撃開始距離
  float_t attackStartDistance_ = 3.0f;
  // 追跡開始距離
  float_t trackingStartDistance_ = 40.0f;

  //発狂状態かどうか
  bool isEnraged_ = false;

  //攻撃(攻撃)
  float_t enragedAttackStartDistance_ = 2.0f;
  //追跡(発狂)
  float_t enragedTrackingStartDistance_ = 2.0f;


  // スピード
  float_t speed_ = 0.1f;
  // 体力
  std::string hpJsonDirectory_ = "Enemys/";
  std::unique_ptr<HealthComponent> hp_ = nullptr;
};
