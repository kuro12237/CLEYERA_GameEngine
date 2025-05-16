#include "NormalEnemyBullet.h"

void NormalEnemyBullet::Init(){
	// 名前の設定
	name_ = VAR_NAME(NormalEnemyBullet);

	// モデルの設定
	uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Sphere", "Sphere");
	gameObject_->ChangeModel(modelHandle);

	// コライダー作成
	CreateCollider(ColliderType::OBB);

	//スケールの設定
	scale_ = { .x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_ };

	translate_.y = 0.5f;
}

void NormalEnemyBullet::Update(){
	//時間
	aliveTime_ += DELTA_TIME_;
	if (aliveTime_ > DELETE_TIME_ ) {
		isDelete_ = true;
	}
	//加速度の計算
	velocityY_ += accel_;
	translate_.y += velocityY_;

	// 更新
	TransformUpdate();

}
