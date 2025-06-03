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
  /// 新しいBulletを追加
  /// </summary>
  void PushbackNewBullet(std::shared_ptr<IPlayerBullet> newBul);

  /// <summary>
  /// ImGuiの描画
  /// </summary>
  void DrawImGui();

private:
  // 発射物の配列
  std::list<std::shared_ptr<IPlayerBullet>> bullets_;
};