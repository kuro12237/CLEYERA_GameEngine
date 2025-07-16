#include "SpecialAttack_NormalBullet.h"


void SpecialAttack_NormalBullet::Init()
{
	// Modelの設定
	uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
																"PlayerDemoBullet");
	ObjectComponent::gameObject_->ChangeModel(handle);

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

void SpecialAttack_NormalBullet::Move() { force_ = initVel_; }