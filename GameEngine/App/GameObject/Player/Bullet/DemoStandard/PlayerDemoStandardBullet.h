#pragma once

#include "../../Attack/Interface/IPlayerBullet.h"

class PlayerDemoStandardBullet : public IPlayerBullet {
public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerDemoStandardBullet();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerDemoStandardBullet() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

private:
  /// <summary>
  /// 移動処理
  /// </summary>
  void Move();
};
