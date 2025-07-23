#include "SpecialAttack_Normal.h"
#include "SpecialAttack_NormalBullet.h"
#include "../../../Core/playerCore.h"

SpecialAttack_Normal::SpecialAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
	lua_ = std::make_unique<LuaScript>();
}

void SpecialAttack_Normal::Init() 
{
    // 弾の出る方向
    directionCount_ = 5;

    // 攻撃のインターバル
    coolDownInterval_ = 3.0f * 60.0f;

}

void SpecialAttack_Normal::Update() 
{
	UpdateCoolDownTimer();
}

void SpecialAttack_Normal::Reset() {}

void SpecialAttack_Normal::IsAttack()
{
    if ( IsCoolDown() )
        return;

    auto bulletManager = bulletManager_.lock();
    if ( !bulletManager )
        return;

    const std::string tagBase = VAR_NAME(SpecialAttack_NormalBullet);
    auto pos = owner_->GetWorldPos();
    auto forward = owner_->GetForwardVec();

    const int count = std::max(1, directionCount_);
    const float angleStep = 2.0f * float(std::numbers::pi) / float(count);
    const float bulletSpeed = 0.3f;

    for ( int i = 0; i < count; ++i )
    {
        float angle = angleStep * i;

        // 弾発射方向を計算
        auto dir = RotateAroundAxis(forward, { 0, 1, 0 }, angle);
        dir = dir * bulletSpeed;

        // 弾生成
        auto bullet = std::make_shared<SpecialAttack_NormalBullet>();
        bullet->SetPosition(pos);
        bullet->SetVelocity(IMagicAttack::CalcVelocity(dir));
        bullet->Init();

        bulletManager->PushbackNewBullet(VAR_NAME(SpecialAttack_NormalBullet),std::move(bullet));

        bulletCount_++;
    }

    SetAttackCoolDown();
}

void SpecialAttack_Normal::DrwaImGui() {}


Math::Vector::Vec3 SpecialAttack_Normal::RotateAroundAxis(const Math::Vector::Vec3 & v,
															   const Math::Vector::Vec3 & axis,
															   float angle) {
	// ロドリゲスの回転公式
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	// v*cosA
	Math::Vector::Vec3 term1 = v * cosA;

	// (axis × v)*sinA
	Math::Vector::Vec3 term2 = Math::Vector::Func::Cross(axis, v) * sinA;

	// axis * (axis・v) * (1 - cosA)
	float dot = Math::Vector::Func::Dot(axis, v);
	Math::Vector::Vec3 term3 = axis * dot * (1.0f - cosA);

	return term1 + term2 + term3;
}