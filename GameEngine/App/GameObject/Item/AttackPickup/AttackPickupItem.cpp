#include "AttackPickupItem.h"



void AttackPickupItem::Init()
{
	name_ = "";
	//// Modelの設定
	//uint32_t handle =
	//	ObjectComponent::modelManager_->LoadModel("Resources/Model/Item/HealItem", "HealItem");
	//ObjectComponent::gameObject_->ChangeModel(handle);
	//
	//// コライダー作成
	//ObjectComponent::CreateCollider(ColliderType::AABB);
}

void AttackPickupItem::Update()
{
	ObjectComponent::TransformUpdate();

}