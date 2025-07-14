#pragma once

/**
 * @file StalkerNormalEnemy.h
 * @brief 雑魚敵3クラス
 * @author 茂木翼
 */

// 一直線

#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "StalkerEnemyBullet.h"

#include"Wall/Wall.h"

/// <summary>
/// 3つ目の雑魚敵
/// </summary>
class StalkerNormalEnemy : public BaseNormalEnemy {
public:
  /// <summary>
  /// 最初のボス
  /// </summary>
  StalkerNormalEnemy() = default;

  /// <summary>
  /// 初期化
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update() override;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~StalkerNormalEnemy() override = default;

  /// <summary>
  /// imGUi
  /// </summary>
  void ImGuiUpdate() override;

public:

  /// <summary>
  /// 衝突
  /// </summary>
  /// <param name="other"></param>
  void OnCollision(std::weak_ptr<ObjectComponent> other);


  /// <summary>
  /// ノックバック
  /// </summary>
  void KnockBack() override;

  /// <summary>
  /// 倒された
  /// </summary>
  void Killed() override;

 
};
