#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "PlayerProjectile .h"

/* プレイヤーの発射物管理クラス */
class PlayerProjectileManager {

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerProjectileManager() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerProjectileManager() = default;

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
  std::weak_ptr<PlayerProjectile> CreateProjectile(const Math::Vector::Vec3 &pos, const Math::Vector::Vec3 &vel, float lifeTime);


private:

  // 発射物の配列
  std::list<std::shared_ptr<PlayerProjectile>> projectiles_;
};