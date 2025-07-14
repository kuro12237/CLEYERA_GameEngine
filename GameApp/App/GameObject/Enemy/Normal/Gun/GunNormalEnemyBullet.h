#pragma once

/**
 * @file GunNormalEnemyBullet.h
 * @brief 雑魚敵(Gun)の弾クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
#include "Component/AttackPower/AttackPower.h"
#include "Enemy/Normal/BaseNormalEnemyBullet.h"

/// <summary>
/// 雑魚敵(Gun)の弾
/// </summary>
class GunNormalEnemyBullet : public BaseNormalEnemyBullet {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  GunNormalEnemyBullet() = default;

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
  ~GunNormalEnemyBullet() = default;

  void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Get
  int32_t GetAttackPower() { return attackPower_->GetPower(); }

#pragma endregion


private:
  /// <summary>
  /// ImGui表示用
  /// </summary>
  void DisplayImGui();

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
