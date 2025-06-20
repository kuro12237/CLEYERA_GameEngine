#pragma once

#include "../../Attack/Interface/IPlayerBullet.h"

class PlayerDemoBullet : public IPlayerBullet {

public:
  struct BulletCurveParams {
    float horizontalCurve = 0.0f;
    float verticalCurve = 0.0f;
    float curveDistance = 0.0f;
  };

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

#pragma region

  // パラメータの設定
  void SetParams(const BulletCurveParams &prams) { params_ = prams; }

#pragma endregion

private:
  /// <summary>
  /// 移動処理
  /// </summary>
  void Move();

private:
  BulletCurveParams params_{}; // パラメータ
  float travelDistance_ = 0.0f;
  Math::Vector::Vec3 direction_{};
  Math::Vector::Vec3 startPos_{};
  float elapsedTime_ = 0.0f; // 経過時間（毎フレーム加算）
};