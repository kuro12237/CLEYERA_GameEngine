#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "../Interface/IPlayerBullet.h"

/* プレイヤーの発射物管理クラス */
class PlayerBulletManager {

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerBulletManager() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerBulletManager() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init();

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

  /// <summary>
  /// 新しいProjectileを生成
  /// </summary>
  std::weak_ptr<IPlayerBullet> CreateProjectile(const Math::Vector::Vec3 &pos, const Math::Vector::Vec3 &vel, float lifeTime);
  
  /// <summary>
  /// ImGuiの描画
  /// </summary>
  void DrawImGui();

private:

  // 発射物の配列
  std::list<std::shared_ptr<IPlayerBullet>> projectiles_;
};