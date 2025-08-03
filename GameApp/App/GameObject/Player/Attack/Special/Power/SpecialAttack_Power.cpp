#include "SpecialAttack_Power.h"
#include "../../../Core/playerCore.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/BaseEnemy.h"

SpecialAttack_Power::SpecialAttack_Power(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr, std::weak_ptr<EnemyManager> eneManaPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr, eneManaPtr);
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
    auto up = Math::Vector::Vec3{0.0f, 35.0f, 0.0f};
    initPos += up;
    newBul->SetPosition(initPos);

    // 初期速度　前方+下向き
    auto forward = owner_->GetForwardVec();
    auto fallDir = forward * 0.3f  + Math::Vector::Vec3{0.0f, -0.1f, 0.0f};
    newBul->SetVelocity(fallDir);

    FindNearestEnemy(owner_->GetWorldPos());

    newBul->SetNearestEnemy(nearestEnemy_);
    newBul->Init();

    bulletManager->PushbackNewBullet(VAR_NAME(SpecialAttack_PowerBullet), std::move(newBul));

    SetAttackCoolDown();
}

void SpecialAttack_Power::DrwaImGui() {}

void SpecialAttack_Power::FindNearestEnemy(const Math::Vector::Vec3 & fromPos)
{
    float minDistSq = std::numeric_limits<float>::max();
    std::shared_ptr<BaseEnemy> closest = nullptr;

    // 雑魚敵をチェック
    auto & enemyList = enemyMgr_.lock()->GetEnemyList();
    for ( const auto & weak : enemyList ) {
        if ( auto enemy = weak.lock() ) {
            float distSq = Math::Vector::Func::Length(enemy->GetPosition() - fromPos);
            if ( distSq < minDistSq ) {
                minDistSq = distSq;
                closest = enemy;
            }
        }
    }

    nearestEnemy_ = closest;
}
