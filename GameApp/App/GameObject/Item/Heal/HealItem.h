#pragma once

#include "../Interface/IItem.h"

/* 回復アイテムクラス */
class HealItem : public IItem {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HealItem() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HealItem() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 衝突時コールバック
	/// </summary>
	void OnCollision(std::weak_ptr<ObjectComponent> other);


#pragma region 

	// 回復値
	uint32_t GetHealValue() const { return healValue_; }

#pragma endregion 

private:

	/// <summary>
	/// 回転処理
	/// </summary>
	void RotateY();

	/// <summary>
	/// 浮遊移動処理
	/// </summary>
	void FloatMove();

private:

	uint32_t healValue_ = 20;

	float rotationAngleY_ = 0.0f; // Y軸回転角度
	float floatTimer_ = 0.0f;     // 上下移動用タイマー
	float baseHeight_ = 0.0f;     // 初期高さ

};
