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
  lifeTime_ = 1.0f * 60.0f;

  // directionを求める
  direction_ = Math::Vector::Func::Normalize(initVel_);
  // 初期座標
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

  float dt = 1.0f / 60.0f; // 60FPS前提
  float moveStep = Math::Vector::Func::Length(initVel_) *dt;
  travelDistance_ += moveStep;

  // 基本の進行方向
  Math::Vector::Vec3 forward = direction_;

  // 曲がり終わる終点 = 始点 + 曲がる距離分進んだ点
  Math::Vector::Vec3 endPos = startPos_ + forward * params_.curveDistance;

  // ラープ進行度
  float t = travelDistance_ / params_.curveDistance;
  t = std::clamp(t, 0.0f, 1.0f);

  // カーブウェイト（0→1→0の山型カーブ）
  float curveWeight = sinf(t * float(std::numbers::pi));

  // right / up ベクトル
  Math::Vector::Vec3 right =
      Math::Vector::Func::Normalize(Math::Vector::Func::Cross({0, 1, 0}, forward));
  Math::Vector::Vec3 up = Math::Vector::Func::Normalize(Math::Vector::Func::Cross(forward, right));

  // オフセット（現在のカーブ位置）
  Math::Vector::Vec3 offset =
      right * params_.horizontalCurve * curveWeight + up * params_.verticalCurve * curveWeight;

  // ラープ位置 = 始点 + 直進ベクトル + オフセット
  Math::Vector::Vec3 targetPos = startPos_ + forward * travelDistance_ + offset;

  // force_ = 移動量 = 新しい位置 - 現在位置
  force_ = targetPos - translate_;
}

/// <summary>
/// 球面補間
/// </summary>
Math::Vector::Vec3 PlayerDemoBullet::Slerp(const Math::Vector::Vec3 &a, const Math::Vector::Vec3 &b,
                                           float t) {
  float dot = std::clamp(Math::Vector::Func::Dot(a, b), -1.0f, 1.0f);
  float theta = acosf(dot) * t;

  Math::Vector::Vec3 relativeVec = Math::Vector::Func::Normalize(b - a * dot);
  return Math::Vector::Func::Normalize(a * cosf(theta) + relativeVec * sinf(theta));
}
