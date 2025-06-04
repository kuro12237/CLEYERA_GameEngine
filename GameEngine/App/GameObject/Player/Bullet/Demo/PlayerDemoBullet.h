#pragma once

#include "../Interface/IPlayerBullet.h"

class PlayerDemoBullet : public IPlayerBullet {

public:
  struct BulletCurveParams {
    float horizontalCurve = 0.0f; // 左右の膨らみ量（負：左、正：右）
    float verticalCurve = 0.0f;   // 上下の膨らみ量（負：下、正：上）
    float curveDistance = 10.0f;  // 曲がりの終点までの距離
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

  /// <summary>
  /// 球面補間
  /// </summary>
  Math::Vector::Vec3 Slerp(const Math::Vector::Vec3 &a, const Math::Vector::Vec3 &b, float t);

private:
  BulletCurveParams params_{}; // パラメータ
  Math::Vector::Vec3 direction_; // 基本の進行方向（正規化）
  float travelDistance_ = 0.0f;  // 累計移動距離
  Math::Vector::Vec3 startPos_;  // 発射位置
};