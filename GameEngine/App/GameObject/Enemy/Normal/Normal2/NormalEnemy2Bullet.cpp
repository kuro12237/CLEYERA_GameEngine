#include "NormalEnemy2Bullet.h"

void NormalEnemy2Bullet::Init() {
	// 名前の設定
	name_ = VAR_NAME(NormalEnemyBullet);

	// モデルの設定
        uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
	gameObject_->ChangeModel(modelHandle);

	// コライダー作成
	CreateCollider(ColliderType::OBB);

	//スケールの設定
	scale_ = { .x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_ };
    translate_ = normalEnemyPosition_;

	//方向を決める
	direction_ = playerPosition_ - translate_;

}

void NormalEnemy2Bullet::Update() {

	//座標の加算
	translate_ += direction_ * SPEED_;

	// 更新
	TransformUpdate();

#ifdef _DEBUG
        DisplayImGui();
#endif // _DEBUG
}

void NormalEnemy2Bullet::DisplayImGui() {
  ImGui::Begin("Bullet2");
  ImGui::InputFloat3("Position", &translate_.x);
  ImGui::End();
	
}
