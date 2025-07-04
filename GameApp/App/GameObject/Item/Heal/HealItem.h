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

	float rotationAngleY_ = 0.0f; // Y軸回転角度
	float floatTimer_ = 0.0f;     // 上下移動用タイマー
	float baseHeight_ = 0.0f;     // 初期高さ

};
