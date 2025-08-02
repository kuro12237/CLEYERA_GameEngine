#include "SpecialAttack_PowerBullet.h"



void SpecialAttack_PowerBullet::Init()
{
	// Modelの設定
	uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
																"PlayerDemoBullet");
	ObjectComponent::gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	SetIsGravity(false);
	SetIsTerrainHit(false);

	scale_ = initialScale_;

	// 生存時間を適当に設定 1秒
	lifeTime_ = 3.0f * 60.0f;

	// 爆発中フラグ初期化
	isExploding_ = false;

	// 爆発エフェクト用タイマー（任意で使う）
	explodeTimer_ = 0.0f;
}


void SpecialAttack_PowerBullet::Update()
{
	if ( !isExploding_ ) {
		Move();

		if ( translate_.y <= 0.5f ) {
			isExploding_ = true;
			explodeTimer_ = 0.0f;
			velocity_ = {};
			force_ = {};
			translate_.y = 0.5f;
		}
	}
	else {
		explodeTimer_ += 1.0f;

		// 総時間（拡大＋収束にかける時間）
		const float explodeDuration = 20.0f; // フレーム数
		float t = std::clamp(explodeTimer_ / explodeDuration, 0.0f, 1.0f);

		// ベジェ的に拡大→収束（t: 0→1）
		// P0: 初期スケール, P1: 最大, P2: 最終スケール
		Math::Vector::Vec3 p0 = initialScale_;
		Math::Vector::Vec3 p1 = explodeScaleMax_;
		Math::Vector::Vec3 p2 = { 0.0f, 0.0f, 0.0f }; // 消えるように収束

		// 2次ベジェ補間で滑らかな拡大→収束
		Math::Vector::Vec3 scale =
			p0 * ((1 - t) * (1 - t)) +
			p1 * (2 * (1 - t) * t) +
			p2 * (t * t);

		scale_ = scale;

		// 完全に収束したら非アクティブ
		if ( t >= 1.0f ) {
			isActive_ = false;
		}
	}

	ObjectComponent::TransformUpdate();
}

void SpecialAttack_PowerBullet::Move() { force_ = initVel_; }