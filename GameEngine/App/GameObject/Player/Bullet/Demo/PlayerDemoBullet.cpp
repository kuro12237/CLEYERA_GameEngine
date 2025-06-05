#include "PlayerDemoBullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerDemoBullet::PlayerDemoBullet() {}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerDemoBullet::Init() {

  // クラス名
  ObjectComponent::name_ = VAR_NAME(PlayerDemoBullet);

  // Modelの設定
  uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
                                                              "PlayerDemoBullet");
  ObjectComponent::gameObject_->ChangeModel(handle);

  // ForceからY軸を求める
  CalcRotateFromVelocity();

  // 生存時間を適当に設定 1秒
  lifeTime_ = 0.5f * 60.0f;

  direction_ = Math::Vector::Func::Normalize(initVel_);
  startPos_ = translate_;
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerDemoBullet::Update() {
  ObjectComponent::TransformUpdate();

  // 移動処理
  Move();
}

/// <summary>
/// 移動処理
/// </summary>
void PlayerDemoBullet::Move() {
  float dt = 1.0f / 60.0f;
  elapsedTime_ += dt;

  float t = elapsedTime_ / (lifeTime_ / 60.0f); // フレーム→秒変換
  t = std::clamp(t, 0.0f, 1.0f);

  // カーブ角
  float angle = t * float(std::numbers::pi);

  Math::Vector::Vec3 forward = direction_;
  Math::Vector::Vec3 right =
      Math::Vector::Func::Normalize(Math::Vector::Func::Cross({0, 1, 0}, forward));
  Math::Vector::Vec3 up = Math::Vector::Func::Normalize(Math::Vector::Func::Cross(forward, right));

  // カーブオフセット
  Math::Vector::Vec3 curveOffset =
      right * params_.horizontalCurve * sinf(angle) + up * params_.verticalCurve * sinf(angle);

  // 弾の速度から進行距離を算出
  float bulletSpeed = Math::Vector::Func::Length(initVel_);
  float totalDistance = bulletSpeed * (lifeTime_ / 60.0f);
  Math::Vector::Vec3 curvePos = forward * (totalDistance * t) + curveOffset;

  Math::Vector::Vec3 newTargetPos = startPos_ + curvePos;
  Math::Vector::Vec3 currentWorldPos = translate_;
  force_ = newTargetPos - currentWorldPos;

  if (angle >= std::numbers::pi) {
    isActive_ = false;
  }
}
