#include "ItemManager.h"
#include "../AttackPickup/AttackPickupItem.h"
#include "../Heal/HealItem.h"

void ItemManager::Init()
{
	// クラス名
	ManagerCompornent::name_ = VAR_NAME(ItemManager);

	attackPickupCount_ = 0;
}


void ItemManager::Update()
{
	ManagerCompornent::ListUpdate();

	// イテレータを使った安全なループ中削除
	for ( auto it = items_.begin(); it != items_.end();) {
;
		// 非アクティブなら削除し、次の有効なイテレータを取得
		if ( !(*it)->IsDead() ) {
			it = items_.erase(it);
		}
		else {
			++it; // アクティブなら次の要素へ
		}
	}
}


void ItemManager::ImGuiUpdate()
{
	if ( ImGui::TreeNode("ItemMananger") ) {
		size_t count = items_.size();
		ImGui::Text("Item Count = %d", count);
		ImGui::Spacing();
		ImGui::Text("AttackPickUp Count = %d", attackPickupCount_);
		ImGui::Text("Heal Count = %d", healCount_);

		ImGui::TreePop();
	}
}


void ItemManager::RegisterItemm(const std::shared_ptr<IItem> & item)
{
	item;
}


void ItemManager::RegisterAttackPickup(const Math::Vector::Vec3 & popPosition)
{
	std::shared_ptr<AttackPickupItem> item = std::make_shared<AttackPickupItem>();
	item->SetPostion(popPosition);
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

void ItemManager::RegisterHealItem(const Math::Vector::Vec3 & popPosition)
{
	std::shared_ptr<HealItem> item = std::make_shared<HealItem>();
	item->SetPostion(popPosition);
	item->Init();

	if ( healCount_ == 0 ) {
		item->SetName(VAR_NAME(HealItem));
	}
	else {
		char name[ 32 ];
		std::snprintf(name, sizeof(name), "HealItem.%03zu", static_cast< size_t >(healCount_));
		item->SetName(name);
	}

	objComponents_.push_back(item);
	items_.push_back(std::move(item));

	healCount_++;
}
