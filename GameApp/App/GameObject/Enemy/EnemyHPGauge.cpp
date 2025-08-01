#include "EnemyHPGauge.h"

#include <Enemy/BaseEnemy.h>

void EnemyHPGauge::Init(){
	// モデルの設定
	uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/EnemyHP", "EnemyHP");
	gameObject_->ChangeModel(modelHandle);

	isGravity_ = false;

	// スケールの設定
	scale_ = { .x = 2.0f, .y = 0.3f, .z = 1.0f };

}

void EnemyHPGauge::Update(){

	translate_.x = baseEnemy_->GetPosition().x + OFFSET_X_;
	translate_.y = baseEnemy_->GetPosition().y + 3.0f;
	translate_.z = baseEnemy_->GetPosition().z;

	if ( baseEnemy_->GetIsDelete() == true ) {
		mode_=CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE;
	}

	maxHP_ = baseEnemy_->GetHealthComponent()->GetMaxHp();
	currentHP = baseEnemy_->GetHealthComponent()->GetHp();
	scale_.x = SCALE_OFFSET_ * float_t(currentHP)/float_t(maxHP_);

#ifdef _DEBUG
	ImGui::Begin("EnemyHPGauge");
	ImGui::InputFloat3("Translate", &translate_.x);
	ImGui::InputInt("CurrentHP", &currentHP);
	ImGui::SliderFloat3("Scale", &scale_.x, 0.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &rotate_.x, 0.0f, 10.0f);

	ImGui::End();
#endif // _DEBUG

	// 更新
	TransformUpdate();
}
