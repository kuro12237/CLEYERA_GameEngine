#include "HighAttack_FieldBullet.h"


void HighAttack_FieldBullet::Init()
{

	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/DemoBullet", "PlayerDemoBullet");
	gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 0.5f * 60.0f;
}

void HighAttack_FieldBullet::Update()
{
	ObjectComponent::TransformUpdate();
	IPlayerBullet::Update_LifeTime();

}
