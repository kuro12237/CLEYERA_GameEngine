#pragma once

#include "../Interface/IPlayerBullet.h"


class PlayerDemoBullet : public IPlayerBullet {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerDemoBullet();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerDemoBullet() = default;

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

private:

  // カーブのパラメータ
  float horizontalCurve_ = 0.0f;
  float verticalCurve_ = 0.0f;

  // カーブの距離
  float curveDistance_ = 0.0f;

  Math::Vector::Vec3 lastPosition_;

};