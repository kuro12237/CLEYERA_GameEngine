#include "SpecialAttack_Power.h"
#include "../../../Core/playerCore.h"

SpecialAttack_Power::SpecialAttack_Power(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
}


void SpecialAttack_Power::Init()
{

}

void SpecialAttack_Power::Update()
{
}

void SpecialAttack_Power::Reset() {}

void SpecialAttack_Power::IsAttack()
{
    auto bulletManager = bulletManager_.lock();

	auto bullet = std::make_shared<SpecialAttack_PowerBullet>();
	bullet->SetPosition(owner_->GetWorldPos());
	bullet->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{0.0f, 0.0f, 1.0f}));
	bullet->SetScale(Math::Vector::Vec3{3.0f, 3.0f, 3.0f});
	bullet->Init();
	bulletManager->PushbackNewBullet(VAR_NAME(SpecialAttack_NormalBullet), std::move(bullet));
}

void SpecialAttack_Power::DrwaImGui() {}
