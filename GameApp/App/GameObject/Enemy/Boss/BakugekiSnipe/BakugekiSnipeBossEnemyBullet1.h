#pragma once

/**
 * @file BakugekiSnipeBossEnemyBullet1.h
 * @brief バクゲキスナイプ(ボス)の弾クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
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
  
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / 60.0f;
    
};
