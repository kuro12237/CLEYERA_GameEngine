#include "HighAttack_Field.h"
#include "../../../Core/playerCore.h"


HighAttack_Field::HighAttack_Field(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr, std::weak_ptr<EnemyManager> eneManaPtr)
{
    IMagicAttack::SetPre(corePtr, bulManagerPtr, eneManaPtr);
}

void HighAttack_Field::Init()
{
    coolDownInterval_ = 0.0f * 60.0f; // 攻撃のインターバル
}

void HighAttack_Field::Update()
{
    UpdateCoolDownTimer();
}

void HighAttack_Field::Reset() {}

void HighAttack_Field::IsAttack()
{
    // 攻撃可能でなければ何もしない
    if ( IsCoolDown() )
        return;

    auto bulletManager = bulletManager_.lock();
    if ( !bulletManager )
        return;

    auto newBul = std::make_shared<HighAttack_FieldBullet>();

    // 初期座標
    newBul->SetPosition(owner_->GetWorldPos());

    // 初期化
    newBul->Init();

    bulletManager->PushbackNewBullet(VAR_NAME(SpecialAttack_PowerBullet), std::move(newBul));

    SetAttackCoolDown();
}

void HighAttack_Field::DrwaImGui() {}

