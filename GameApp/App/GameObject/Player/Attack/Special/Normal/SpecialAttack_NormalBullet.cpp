#include "SpecialAttack_NormalBullet.h"
#include "../../../Core/playerCore.h"


void SpecialAttack_NormalBullet::Init()
{
	// Modelの設定
	uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/Bullet",
																"Bullet");
	ObjectComponent::gameObject_->ChangeModel(handle);

	// 当たり判定関数セット
	collider_->SetHitCallFunc(
		[this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 3.0f * 60.0f;
}


void SpecialAttack_NormalBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

	// 移動処理
	Move();
}

void SpecialAttack_NormalBullet::OnCollision(std::weak_ptr<ObjectComponent> other)
{
	auto obj = other.lock();
	// Player型にキャストできるかをチェック
	if ( auto p = std::dynamic_pointer_cast< PlayerCore >(obj) ) {
		return;
	}
	if ( auto p = std::dynamic_pointer_cast< IPlayerBullet >(obj) ) {
		return;
	}

	isActive_ = true;
}


void SpecialAttack_NormalBullet::Move() { force_ = initVel_; }