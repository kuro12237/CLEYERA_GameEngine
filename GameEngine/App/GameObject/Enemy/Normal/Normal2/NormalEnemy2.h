#pragma once

/**
 * @file NormalEnemy2Bullet.h
 * @brief 雑魚敵2クラス
 * @author 茂木翼
 */

// 一直線

#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "NormalEnemy2Bullet.h"

#include"Wall/Wall.h"

/// <summary>
/// 最初の敵
/// </summary>
class NormalEnemy2 : public BaseNormalEnemy {
public:
  /// <summary>
  /// 最初のボス
  /// </summary>
  NormalEnemy2() = default;

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
  ~NormalEnemy2() override = default;

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
