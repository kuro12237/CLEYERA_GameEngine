#pragma once

#include <CLEYERA.h>
#include "../Interface/IItem.h"


/* IItemを継承しているObjectを管理するクラス */
class ItemManager : public CLEYERA::Component::ManagerCompornent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemManager() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// ImGui表示
	/// </summary>
	void ImGuiUpdate() override;

	/// <summary>
	/// ItemをListに登録
	/// </summary>
	void RegisterItemm(const std::shared_ptr<IItem> & item);	
	
	/// <summary>
	/// 攻撃ピックアップアイテムを登録
	/// </summary>
	void RegisterAttackPickup(const Math::Vector::Vec3& popPosition);

	/// <summary>
	/// 回復アイテムを登録
	/// </summary>
	void RegisterHealItem(const Math::Vector::Vec3 & popPosition);


private:

	std::list<std::shared_ptr<IItem>>items_;
	uint32_t attackPickupCount_ = 0;
	uint32_t healCount_ = 0;

};

