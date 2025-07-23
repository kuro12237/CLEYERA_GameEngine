#include "SpecialAttack_Power.h"
#include "../../../Core/playerCore.h"

SpecialAttack_Power::SpecialAttack_Power(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
}


void SpecialAttack_Power::Init()
{

	// 攻撃のインターバル
	coolDownInterval_ = 0.0f * 60.0f;
}

void SpecialAttack_Power::Update()
{
	UpdateCoolDownTimer();
}

void SpecialAttack_Power::Reset() {}

void SpecialAttack_Power::IsAttack()
{
    if ( IsCoolDown() )
        return;

    auto bulletManager = bulletManager_.lock();
    if ( !bulletManager )
        return;

    auto newBul = std::make_shared<SpecialAttack_PowerBullet>();

    // 初期座標　player上空
    auto initPos = owner_->GetWorldPos();
    auto up = Math::Vector::Vec3{0.0f, 15.0f, 0.0f};
    initPos += up;
    newBul->SetPosition(initPos);

    // 初期速度　前方+下向き
    auto forward = owner_->GetForwardVec();
    auto fallDir = forward * 1.5f  + Math::Vector::Vec3{0.0f, -1.0f, 0.0f};
    newBul->SetVelocity(fallDir);

    newBul->Init();

    bulletManager->PushbackNewBullet(VAR_NAME(SpecialAttack_PowerBullet), std::move(newBul));

    SetAttackCoolDown();
}

void SpecialAttack_Power::DrwaImGui() {}
