#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "PlayerProjectile .h"

/* プレイヤーの発射物管理クラス */
class ProjectileManager {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  ProjectileManager() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~ProjectileManager() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init();

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

private:

  // 発射物の配列
  std::list<std::unique_ptr<PlayerProjectile>> projectiles_;
};