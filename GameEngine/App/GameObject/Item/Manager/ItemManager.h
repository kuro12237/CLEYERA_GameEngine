#pragma once

#include "CLEYERA.h"
#include "../Interface/IItem.h"


/* IItemを継承しているObjectを管理するクラス */
class ItemManager : public CLEYERA::Component::ManagerCompornent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemManager() = default;

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
	void RegisterItem(std::shared_ptr<IItem> item);

private:

};

