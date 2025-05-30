#include "NormalEnemy2Bullet.h"

void NormalEnemy2Bullet::Initialize(const Math::Vector::Vec3 &enemyPosition,
                                    const Math::Vector::Vec3 &playerPositio) {
	// 名前の設定
	name_ = VAR_NAME(NormalEnemyBullet);

	// モデルの設定
    uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
	gameObject_->ChangeModel(modelHandle);

	// コライダー作成
	CreateCollider(ColliderType::OBB);

	//スケールの設定
	scale_ = { .x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_ };
    translate_ = enemyPosition;

	//方向を決める
    direction_ = playerPositio - translate_;
    direction_ = Math::Vector::Func::Normalize(direction_);
}

void NormalEnemy2Bullet::Update() {

	//最大5秒まで表示その後に消える
	displayTime_ += DELTA_TIME_;
	if (displayTime_ > MAX_DISPLAY_TIME_) {
          isDelete_ = true;
	}

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
  ImGui::InputFloat3("Direction", &direction_.x);
  ImGui::InputFloat3("Position", &translate_.x);
  ImGui::End();
	
}
