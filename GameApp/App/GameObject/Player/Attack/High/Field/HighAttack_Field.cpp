#include "HighAttack_Field.h"
#include "../../../Core/playerCore.h"


HighAttack_Field::HighAttack_Field(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
    IMagicAttack::SetPre(corePtr, bulManagerPtr);
}

void HighAttack_Field::Init()
{
    coolDownInterval_ = 2.0f * 60.0f; // 攻撃のインターバル
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



}

void HighAttack_Field::DrwaImGui() {}

