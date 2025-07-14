#pragma once

/**
 * @file GunNormalEnemyBullet.h
 * @brief 雑魚敵2クラス
 * @author 茂木翼
 */


#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "GunNormalEnemyBullet.h"

#include"Wall/Wall.h"

/// <summary>
/// 雑魚敵(Gun)
/// </summary>
class GunNormalEnemy : public BaseNormalEnemy {
public:
  /// <summary>
  /// 最初のボス
  /// </summary>
  GunNormalEnemy() = default;

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
  ~GunNormalEnemy() override = default;

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
