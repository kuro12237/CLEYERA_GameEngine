#pragma once

#include "../Interface/IItem.h"

/* 攻撃をチェンジするピックアップアイテムクラス */
class AttackPickupItem : public IItem {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	AttackPickupItem() {};
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~AttackPickupItem() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

};

