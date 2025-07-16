#pragma once

/**
 * @file CannonNormalEnemy.h
 * @brief 雑魚敵1クラス
 * @author 茂木翼
 */

// 詳しい挙動とかはここにあるよ
// https://docs.google.com/presentation/d/1LTi0n_xoAkvzk13g5KMXGNqeEhtBJlnYJjtetUjhM7M/edit#slide=id.p

#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"

#include "Wall/Wall.h"

/// <summary>
///	ドーナツ
/// </summary>
class DonutNormalEnemy : public BaseNormalEnemy {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DonutNormalEnemy() = default;

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
  ~DonutNormalEnemy() override = default;

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
