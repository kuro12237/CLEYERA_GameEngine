#include "SpecialAttack_PowerBullet.h"
#include "Enemy/BaseEnemy.h"
#include "../../../Core/playerCore.h"


void SpecialAttack_PowerBullet::Init()
{
	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/Bullet2", "Bullet2");
	ObjectComponent::gameObject_->ChangeModel(handle);

	// 当たり判定関数セット
	collider_->SetHitCallFunc(
		[this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	attackPower_->SetPower(50);

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

	auto aabb = std::dynamic_pointer_cast< CLEYERA::Util::Collider::AABBCollider >(collider_);
	if ( aabb ) {
		Math::Vector::Vec3 half = {
			0.5f * scale_.x,
			0.5f * scale_.y,
			0.5f * scale_.z
		};
		Math::Vector::Vec3 min = {
			-half.x,
			-half.y,
			-half.z
		};
		Math::Vector::Vec3 max = half;

		aabb->SetSize(min, max);
	}

	ObjectComponent::TransformUpdate();

	ObjectComponent::TransformUpdate();
}

void SpecialAttack_PowerBullet::OnCollision(std::weak_ptr<ObjectComponent> other)
{
	auto obj = other.lock();
	// Player型にキャストできるかをチェック
	if ( auto p = std::dynamic_pointer_cast< PlayerCore >(obj) ) {
		return;
	}
	if ( auto p = std::dynamic_pointer_cast< IPlayerBullet >(obj) ) {
		return;
	}

}

void SpecialAttack_PowerBullet::Move() 
{
	force_ = initVel_; 

	//const float maxHomingDistance = 0.0f; // 追尾する最大距離

	//if ( homingFrames_ > 0 ) {
	//	if ( auto enemy = nearestEnemy_.lock() ) {
	//		Math::Vector::Vec3 targetPos = enemy->GetPosition();
	//		Math::Vector::Vec3 toEnemy = targetPos - translate_;
	//		float distance = Math::Vector::Func::Length(toEnemy);

	//		if ( distance <= maxHomingDistance ) {
	//			// 敵が近い場合は追尾
	//			Math::Vector::Vec3 direction = Math::Vector::Func::Normalize(toEnemy);
	//			float speed = Math::Vector::Func::Length(initVel_);
	//			velocity_ = direction * speed;
	//			force_ = velocity_;

	//			// 向き補正
	//			CalcRotateFromVelocity();
	//		}
	//		else {
	//			// 敵が遠すぎたら直進
	//			velocity_ = initVel_;
	//			force_ = velocity_;
	//		}
	//	}
	//	else {
	//		// 敵が無効になったら直進
	//		velocity_ = initVel_;
	//		force_ = velocity_;
	//	}
	//	--homingFrames_;
	//}
	//else {
	//	// 追尾期間を過ぎたら直進
	//	velocity_ = initVel_;
	//	force_ = velocity_;
	//}
}