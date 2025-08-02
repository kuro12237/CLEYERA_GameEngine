#include "HighAttack_FieldBullet.h"


void HighAttack_FieldBullet::Init()
{
	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/DemoBullet", "PlayerDemoBullet");
	gameObject_->ChangeModel(handle);

	// ForceからY軸を求める
	CalcRotateFromVelocity();

    // スケールアニメ用
    expandDuration_ = 10.0f;  // 30フレーム拡大
    shrinkDuration_ = 10.0f;  // 30フレーム収縮
    maxScale_ = 15.0f;         // 好きな最大サイズ

    phase_ = Expand;
    frameCount_ = 0;

    scale_ = { 0.1f, 0.5f, 0.1f };
}

void HighAttack_FieldBullet::Update()
{
	ObjectComponent::TransformUpdate();
    Wave();
}

void HighAttack_FieldBullet::Wave()
{
    frameCount_++;

    float scale = 1.0f;

    if ( phase_ == Expand ) {
        float expandT = std::min(frameCount_ / expandDuration_, 1.0f);
        scale = Math::Vector::Func::Lerp(0.1f, maxScale_, expandT);
        if ( expandT >= 1.0f ) {
            phase_ = Shrink;
            frameCount_ = 0;
        }
    }
    else if ( phase_ == Shrink ) {
        float shrinkT = std::min(frameCount_ / shrinkDuration_, 1.0f);
        scale = Math::Vector::Func::Lerp(maxScale_, 0.0f, shrinkT);
        if ( shrinkT >= 1.0f ) {
            isActive_ = true;
        }
    }

    scale_.x = scale;
    scale_.y = 0.5f;
    scale_.z = scale;

    gameObject_->SetScale(scale_);
}
