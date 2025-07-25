#pragma once

/**
 * @file BakugekiSnipeBossEnemyBullet2.h
 * @brief バクゲキスナイプの弾2クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
#include "Component/AttackPower/AttackPower.h"
#include <Enemy/Boss/BaseBossEnemyBullet.h>

/// <summary>
/// ボス敵の弾2
/// </summary>
class BakugekiSnipeBossEnemyBullet2 : public BaseBossEnemyBullet {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  BakugekiSnipeBossEnemyBullet2() = default;

  /// <summary>
  /// 初期化
  /// </summary>
  void Initialize(const Math::Vector::Vec3 &enemyPosition,
                  const Math::Vector::Vec3 &playerPosition) override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update() override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~BakugekiSnipeBossEnemyBullet2() = default;

  void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Get
  int32_t GetAttackPower() { return attackPower_->GetPower(); }

#pragma endregion

private:
  // スケールサイズ
  const float_t SCALE_SIZE_ = 0.5f;
  // 地面の高さ
  const float_t GROUND_HEIGHT_ = 0.0f;
  // FPS
  const float_t FPS_VALUE_ = 60.0f;
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / FPS_VALUE_;
  // 攻撃時間
  const float_t ATTACK_ALL_TIME_ = 1.0f;
  // 高さ
  float_t HEIGHT_ = 4.0f;
  // 消える時間
  const float_t DELETE_TIME_ = 1.0f;

private:
  // 取得し終わったかどうか
  bool isGetNormalEnemyPosition_ = false;

  // 取得し終わったかどうか
  bool isGetPlayerPosition_ = false;

  // 時間
  float_t aliveTime_ = 0.0f;

  // 加速度
  float_t velocityY_ = 0.5f;
  float_t accel_ = -0.01f;

  const float_t INCREASE_T_VALUE_ = 0.01f;
  float_t t_ = 0.0f;

};
