#include "LowAttack_Back.h"
#include "LowAttack_BackBullet.h"
#include "../../../Core/playerCore.h"


LowAttack_Back::LowAttack_Back(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
	lua_ = std::make_unique<LuaScript>();
}

void LowAttack_Back::Init()
{
    // 攻撃のインターバル
    coolDownInterval_ = 0.5f * 60.0f;
}

void LowAttack_Back::Update()
{
    UpdateCoolDownTimer();
}

void LowAttack_Back::Reset()
{

}

void LowAttack_Back::IsAttack()
{
    if ( IsCoolDown() )
        return;

    auto bulletManager = bulletManager_.lock();
    if ( !bulletManager )
        return;

    auto pos = owner_->GetWorldPos();
    auto forward = owner_->GetForwardVec();
    auto back = forward * -1.0f;

    // 発射方向（-30°, 0°, +30°）を back を基準に回転
    std::vector<float> angleOffsets = {
        DegreesToRadians(-30.0f),
        DegreesToRadians(0.0f),
        DegreesToRadians(30.0f)
    };

    float bulletSpeed = 1.0f;

    for ( float angle : angleOffsets ) {
        Math::Vector::Vec3 dir = RotateAroundAxis(back, { 0, 1, 0 }, angle);

        auto newBul = std::make_shared<LowAttack_BackBullet>();
        newBul->SetPosition(pos);
        newBul->SetVelocity(dir * bulletSpeed);
        newBul->Init();

        // 名前設定
        if ( bulletCount_ == 0 ) {
            newBul->SetName(VAR_NAME(LowAttack_BackBullet));
        }
        else {
            char name[ 32 ];
            std::snprintf(name, sizeof(name), "LowAttack_BackBullet.%03zu", bulletCount_);
            newBul->SetName(name);
        }

        bulletManager->PushbackNewBullet(VAR_NAME(LowAttack_BackBullet),std::move(newBul));
        bulletCount_++;
    }

    SetAttackCoolDown();
}

void LowAttack_Back::DrwaImGui()
{
	
}

Math::Vector::Vec3 LowAttack_Back::RotateAroundAxis(const Math::Vector::Vec3 & v, const Math::Vector::Vec3 & axisRaw, float angle)
{
    Math::Vector::Vec3 axis = Math::Vector::Func::Normalize(axisRaw);  // 念のため正規化

    float cosA = cosf(angle);
    float sinA = sinf(angle);

    // ロドリゲスの回転公式
    Math::Vector::Vec3 term1 = v * cosA;
    Math::Vector::Vec3 term2 = Math::Vector::Func::Cross(axis, v) * sinA;
    Math::Vector::Vec3 term3 = axis * Math::Vector::Func::Dot(axis, v) * (1.0f - cosA);

    return term1 + term2 + term3;
}

float LowAttack_Back::DegreesToRadians(float deg)
{
    return deg * (std::numbers::pi_v<float> / 180.0f);
}
