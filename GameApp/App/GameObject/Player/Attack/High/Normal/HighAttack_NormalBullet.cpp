#include "HighAttack_NormalBullet.h"


void HighAttack_NormalBullet::Init()
{

	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/DemoBullet", "PlayerDemoBullet");
	gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 0.5f * 60.0f;
}

void HighAttack_NormalBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

	// 移動処理
	Move();
}

void HighAttack_NormalBullet::Move() { force_ += initVel_; }