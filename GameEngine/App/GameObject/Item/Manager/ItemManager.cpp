#include "ItemManager.h"
#include "../AttackPickup/AttackPickupItem.h"

void ItemManager::Init()
{
	// クラス名
	ManagerCompornent::name_ = VAR_NAME(ItemManager);

	attackPickupCount_ = 0;
}


void ItemManager::Update()
{
	ManagerCompornent::ListUpdate();

}


void ItemManager::ImGuiUpdate()
{
	if ( ImGui::TreeNode("ItemMananger") ) {
		size_t count = objComponents_.size();
		ImGui::Text("Item Count = %d", count);

		ImGui::Spacing();
		ImGui::Text("AttackPickUp Count = %d", attackPickupCount_);

		ImGui::TreePop();
	}
}


void ItemManager::RegisterItem(std::shared_ptr<IItem> item)
{
	if ( item ) {
		objComponents_.push_back(std::move(item));
		items_.push_back(item);
	}
}

void ItemManager::RegisterAttackPickup()
{
	std::shared_ptr<AttackPickupItem> item = std::make_shared<AttackPickupItem>();
	item->Init();

	if ( attackPickupCount_ == 0 ) {
		item->SetName(VAR_NAME(AttackPickupItem));
	}
	else {
		char name[ 32 ];
		std::snprintf(name, sizeof(name), "AttackPickupItem.%03zu", static_cast< size_t >(attackPickupCount_));
		item->SetName(name);
	}

	objComponents_.push_back(item);
	items_.push_back(std::move(item));

	attackPickupCount_++;
}