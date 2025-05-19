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
        translate_ = normalEnemyPosition_;

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

	//線形補間でXZ
        t_ +=  1.0f/(ATTACK_ALL_TIME_ * FPS_VALUE_);
        float startY = normalEnemyPosition_.y;
        float endY = playerPosition_.y;

        float baseY = std::lerp(startY, endY, t_);
        translate_.y = sin(t_ * std::numbers::pi_v<float_t>) * HEIGHT_ + baseY;
	translate_.x = Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).x;
        translate_.z = Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).z;

	// 更新
	TransformUpdate();

	#ifdef _DEBUG
        ImGui::Begin("Bullet");
        ImGui::InputFloat3("座標", &translate_.x);
        ImGui::InputFloat("T", &t_);
        ImGui::End();
#endif // _DEBUG
        


}
