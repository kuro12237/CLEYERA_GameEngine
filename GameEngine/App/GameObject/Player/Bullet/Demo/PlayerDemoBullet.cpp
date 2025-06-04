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

  // 生存時間を適当に設定 1秒
  lifeTime_ = 1.0f * 60.0f;

  // ForceからY軸を求める
  CalcRotateFromVelocity();
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

  elapsedTime_ += 1.0f / 60.0f;

  // 進行ベース
  float progress = 0.0f;
  if (param_.useDistance) {
    traveledDistance_ += initVel_.z;
    progress = std::clamp(traveledDistance_ / param_.curveDistance, 0.0f, 1.0f);
  } else {
    progress = std::clamp(elapsedTime_ / param_.curveTime, 0.0f, 1.0f);
  }

  float curveX = 0.0f, curveY = 0.0f;

  switch (param_.type) {
  case PlayerDemoBulletParam::CurveType::SinWave:
    curveX = param_.horizontalCurve * sinf(progress * float(std::numbers::pi));
    curveY = param_.verticalCurve * sinf(progress * float(std::numbers::pi));
    break;

  case PlayerDemoBulletParam::CurveType::Linear:
    curveX = param_.horizontalCurve * progress;
    curveY = param_.verticalCurve * progress;
    break;

  case PlayerDemoBulletParam::CurveType::EaseInOut:
    curveX = param_.horizontalCurve * powf(sinf(progress * float(std::numbers::pi) / 2.0f), 2.0f);
    curveY = param_.verticalCurve * powf(sinf(progress * float(std::numbers::pi) / 2.0f), 2.0f);
    break;

  case PlayerDemoBulletParam::CurveType::None:
  default:
    break;
  }

  // 合成された速度
  Math::Vector::Vec3 velocity = initVel_;
  velocity.x += curveX;
  velocity.y += curveY;

  force_ = velocity;

  // ここで isActive を false にする条件を加える
  if (param_.useDistance) {
    if (traveledDistance_ >= param_.curveDistance) {
      isActive_ = false;
    }
  } else {
    if (elapsedTime_ >= param_.curveTime) {
      isActive_ = false;
    }
  }
}
