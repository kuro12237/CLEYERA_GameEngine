#include "LowAttack_NormalBullet.h"
#include <algorithm>

void LowAttack_NormalBullet::Init()
{
	// クラス名
	//name_ = VAR_NAME(LowAttack_NormalBullet);

	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/DemoBullet",	"PlayerDemoBullet");
	gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 1.0f * 60.0f;

    elapsedTime_ = 0.0f;
}

void LowAttack_NormalBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

    // 移動処理
    if ( comboStep_ == 1 ) {
        CurveMove();
    }
    else if ( comboStep_ == 2 ) {
        CurveMove();
    }
    else if ( comboStep_ == 3 ) {
        StraightMove();
    }
}

void LowAttack_NormalBullet::CurveMove()
{
    // 統一したスピードにする（フレームあたり距離）
    float fixedSpeed = 1.0f;
    traveledDistance_ += fixedSpeed;

    // 総距離に対するt（0～1）
    float t = std::clamp(traveledDistance_ / travelDistance_, 0.0f, 1.0f);

    // 基本軸ベクトル
    Math::Vector::Vec3 forward = Math::Vector::Func::Normalize(initVel_);
    Math::Vector::Vec3 right = Math::Vector::Func::Normalize(Math::Vector::Func::Cross({ 0,1,0 }, forward));

    // カーブ方向による反転
    float signedMagnitude = (comboStep_ == 2) ? -curveMagnitude_ : curveMagnitude_;
    Math::Vector::Vec3 p0 = initPos_;
    Math::Vector::Vec3 p2 = initPos_ + forward * travelDistance_;
    Math::Vector::Vec3 p1 = initPos_ + forward * (travelDistance_ * 0.25f) + right * signedMagnitude;

    // 2次ベジェ補間
    Math::Vector::Vec3 bezierPos =
        p0 * ((1 - t) * (1 - t)) +
        p1 * (2 * (1 - t) * t) +
        p2 * (t * t);

    force_ = bezierPos - gameObject_->GetWorldPos();
}

void LowAttack_NormalBullet::StraightMove()
{ 
    force_ = initVel_;
}

