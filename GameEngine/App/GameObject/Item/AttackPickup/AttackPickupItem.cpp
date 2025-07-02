#include "AttackPickupItem.h"



void AttackPickupItem::Init()
{
	ObjectComponent::name_ = VAR_NAME(AttackPickupItem);

	// Modelの設定
	uint32_t handle =
		ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
	ObjectComponent::gameObject_->ChangeModel(handle);
	uint32_t demo = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
															  "PlayerDemoBullet");
	demo;

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::AABB);
}

void AttackPickupItem::Update()
{

}