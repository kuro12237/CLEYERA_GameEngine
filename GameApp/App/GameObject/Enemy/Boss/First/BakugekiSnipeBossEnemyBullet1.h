#pragma once

/**
 * @file BakugekiSnipeBossEnemyBullet1.h
 * @brief バクゲキスナイプ(ボス)の弾クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
#include "Component/AttackPower/AttackPower.h"
#include "Enemy/Boss/BaseBossEnemyBullet.h"

/// <summary>
/// ボス敵の弾
/// </summary>
class BakugekiSnipeBossEnemyBullet1 : public BaseBossEnemyBullet {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  BakugekiSnipeBossEnemyBullet1() = default;

  /// <summary>
  /// 初期化
  /// </summary>
  void Initialize(const Math::Vector::Vec3 &enemyPosition,
                  const Math::Vector::Vec3 &playerPositio) override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update() override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~BakugekiSnipeBossEnemyBullet1() = default;

  void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Get
  int32_t GetAttackPower() { return attackPower_->GetPower(); }

#pragma endregion


private:
  // スケールサイズ
  const float_t SCALE_SIZE_ = 1.0f;
  // 弾の速さ
  const float_t SPEED_ = 0.5f;
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / 60.0f;
  // 最大表示時間
  const float_t MAX_DISPLAY_TIME_ = 5.0f;

private:
  // 方向
  Math::Vector::Vec3 direction_ = {};

  // 表示時間
  float_t displayTime_ = 0.0f;

  std::unique_ptr<AttackPower> attackPower_ = nullptr;
};
