#include "LowAttack_NormalBullet.h"
#include <algorithm>

void LowAttack_NormalBullet::Init()
{
	// クラス名
	name_ = VAR_NAME(LowAttack_NormalBullet);

	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/DemoBullet",	"PlayerDemoBullet");
	gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 0.5f * 60.0f;

    elapsedTime_ = 0.0f;
}

void LowAttack_NormalBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

    // 移動処理
    if ( comboStep_ >= 2 ) {
        StraightMove();
    }
    else {
        CurveMove();
    }
}

void LowAttack_NormalBullet::CurveMove()
{
    // 進む距離（1frameの速度）
    float frameSpeed = Math::Vector::Func::Length(initVel_);
    traveledDistance_ += frameSpeed;

    // 総距離に応じた t（0～1）を算出
    float t = std::clamp(traveledDistance_ / travelDistance_, 0.0f, 1.0f);

    // 軌道構成
    Math::Vector::Vec3 forward = Math::Vector::Func::Normalize(initVel_);
    Math::Vector::Vec3 right = Math::Vector::Func::Normalize(Math::Vector::Func::Cross({ 0,1,0 }, forward));

    // ComboStepが1なら左カーブ
    if ( comboStep_ == 1 ) {
        right = right * -1.0f;
    }

    Math::Vector::Vec3 p0 = initPos_;
    Math::Vector::Vec3 p2 = initPos_ + forward * travelDistance_;
    Math::Vector::Vec3 p1 = initPos_ + forward * (travelDistance_ * 0.25f) + right * curveMagnitude_;

    // ベジェ補間
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

