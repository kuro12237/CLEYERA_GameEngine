#include "HealItem.h"



void HealItem::Init()
{
	ObjectComponent::name_ = VAR_NAME(HealItem);

	// Modelの設定
	uint32_t handle =
		ObjectComponent::modelManager_->LoadModel("Resources/Model/Item/HealItem", "HealItem");
	ObjectComponent::gameObject_->ChangeModel(handle);

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::AABB);
}

void HealItem::Update()
{
	ObjectComponent::TransformUpdate();

	// 回転処理
	RotateY();
	// 浮遊処理
	FloatMove();
}

void HealItem::RotateY()
{
	float rotateSpeed = 1.0f; 
	rotationAngleY_ += rotateSpeed * (1.0f / 60.0f);

	// 0-360度に正規化
	if ( rotationAngleY_ >= 360.0f ) {
		rotationAngleY_ -= 360.0f;
	}

	// Transform更新
	rotate_ = { 0.0f, rotationAngleY_, 0.0f };
}

void HealItem::FloatMove()
{
	floatTimer_ += (1.0f / 60.0f);

	float floatHeight = 0.5f; // 振れ幅（上下0.3m動く）
	float floatSpeed = 2.0f;  // 1秒間に2πラジアン進む(周期約3.14秒)

	float offsetY = sinf(floatTimer_ * floatSpeed) * floatHeight;

	// Transform更新
	translate_.y = baseHeight_ + offsetY;
}
