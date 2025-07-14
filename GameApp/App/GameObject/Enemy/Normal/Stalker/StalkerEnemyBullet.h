#pragma once

/**
 * @file StalkerEnemyBullet.h
 * @brief 雑魚敵3の弾クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
#include "Component/AttackPower/AttackPower.h"
#include "Enemy/Normal/BaseNormalEnemyBullet.h"

/// <summary>
/// 追跡の敵の弾
/// </summary>
class StalkerEnemyBullet : public BaseNormalEnemyBullet {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  StalkerEnemyBullet() = default;

  /// <summary>
  /// 初期化
  /// </summary>
  /// <param name="enemyPosition"></param>
  /// <param name="playerPosition"></param>
  /// <param name="isPersistentlyTrack"></param>
  void Initialize(const Math::Vector::Vec3 &enemyPosition, const Math::Vector::Vec3 &playerPosition,
                  const bool &isPersistentlyTrack) override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update() override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~StalkerEnemyBullet() = default;

  void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Get
  int32_t GetAttackPower() { return attackPower_->GetPower(); }

#pragma endregion


private:
  // スケールサイズ
  const float_t SCALE_SIZE_ = 1.0f;
  // 弾の速さ
  const float_t SPEED_ = 0.2f;
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / 60.0f;
  // 最大表示時間
  const float_t MAX_DISPLAY_TIME_ = 5.0f;
  //スケールダウン
  const float_t SCALE_DOWN_VALUE_ = 0.1f;
  //消えるサイズ
  const float_t DELETE_SCALE_ = 0.0f;
  //追跡時間制限
  const float_t TRACKING_LIMIT_TIME_ = 1.0f;

private:
  // 方向
  Math::Vector::Vec3 direction_ = {};
  //追跡時間
  float_t trackingTime_ = 0.0f;

  // 表示時間
  float_t displayTime_ = 0.0f;

  std::unique_ptr<AttackPower> attackPower_ = nullptr;
};
