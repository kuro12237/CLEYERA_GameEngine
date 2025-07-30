#include "SpecialAttack_PowerBullet.h"



void SpecialAttack_PowerBullet::Init()
{
	// Modelの設定
	uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
																"PlayerDemoBullet");
	ObjectComponent::gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

	// 生存時間を適当に設定 1秒
	lifeTime_ = 3.0f * 60.0f;

	// 爆発中フラグ初期化
	isExploding_ = false;

	// 爆発エフェクト用タイマー（任意で使う）
	explodeTimer_ = 0.0f;
}


void SpecialAttack_PowerBullet::Update()
{
	ObjectComponent::TransformUpdate();

	if ( !isExploding_ ) {
		// 移動
		Move();

		// 高さチェックして爆発に遷移
		if ( translate_.y <= 0.5f ) {
			isExploding_ = true;
			explodeTimer_ = 0.0f;
		}
	}
	else {
		// 爆発中：スケール拡大処理
		const float scaleSpeed = 0.05f;
		scale_ += {scaleSpeed, scaleSpeed, scaleSpeed};

		// 時間経過後に削除
		explodeTimer_ += 1.0f;
		if ( explodeTimer_ >= 10.0f ) { // 約10フレーム後
			isActive_ = false;
		}
	}
}

void SpecialAttack_PowerBullet::Move() { force_ = initVel_; }