#pragma once

/**
 * @file BaseNormalEnemy.h
 * @brief 敵の基底クラス
 * @author 茂木翼
 */

#include "CLEYERA.h"
#include "Enemy/EnemyParameter.h"

/// <summary>
/// 敵の基底クラス
/// </summary>
class BaseNormalEnemy : public CLEYERA::Component::ObjectComponent {
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

protected:
  // プレイヤー座標
  Math::Vector::Vec3 playerPosition_ = {};
  // パラメーター
  EnemyParameter parameter_ = {};
};