#include "LowAttack_BackBullet.h"
#include "../../../Core/playerCore.h"

void LowAttack_BackBullet::Init()
{
	// クラス名
	name_ = VAR_NAME(LowAttack_BackBullet);

	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/Bullet", "Bullet");
	gameObject_->ChangeModel(handle);

	// 当たり判定関数セット
	collider_->SetHitCallFunc(
		[this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 0.5f * 60.0f;
}


void LowAttack_BackBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

	// 移動処理
	Move();
}

void LowAttack_BackBullet::OnCollision(std::weak_ptr<ObjectComponent> other)
{
	auto obj = other.lock();
	// Player型にキャストできるかをチェック
	if ( auto p = std::dynamic_pointer_cast< PlayerCore >(obj) ) {
		return;
	}
	if ( auto p = std::dynamic_pointer_cast< IPlayerBullet >(obj) ) {
		return;
	}

	isActive_ = false;
}

void LowAttack_BackBullet::Move() { force_ += initVel_; }