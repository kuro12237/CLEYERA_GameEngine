#include "ItemManager.h"


void ItemManager::Init()
{
	// クラス名
	ManagerCompornent::name_ = VAR_NAME(ItemManager);
}


void ItemManager::Update()
{
	// 更新
	ManagerCompornent::ListUpdate();
}


void ItemManager::ImGuiUpdate()
{
	if ( ImGui::TreeNode("ItemMananger") ) {
		size_t count = objComponents_.size();
		ImGui::Text("Item Count = %d", count);

		ImGui::TreePop();
	}
}


void ItemManager::RegisterItem(std::shared_ptr<IItem> item)
{
	if ( item ) {
		item->Init(); // 初期化
		objComponents_.push_back(std::move(item));
	}
}