#pragma once

#include "CLEYERA.h"

// 前方宣言
class PlayerCore;

/* Playerの体力管理クラス */
class PlayerHealth {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerHealth(PlayerCore *corePtr);

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerHealth() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init(float initHealth = 0);

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

#pragma region

  float GetHealth() const { return health_; }
  void SetHealth(float set) { health_ = set; }

  void AddHealth(float add) { health_ += add; }
  void SubHealth(float sub) { health_ -= sub; }

#pragma endregion

private:
  // 親
  PlayerCore *owner_ = nullptr;

  // 体力
  float health_ = 0.0f;
};
