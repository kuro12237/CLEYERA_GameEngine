#include "PlayerAttackDemoBasic.h"
#include "../../../playerCore.h"
#include "../../../../Projectile/PlayerProjectileManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoBasic::PlayerAttackDemoBasic(PlayerCore* corePtr, PlayerProjectileManager* projManagerPtr)
{
  IMagicAttack::SetPre(corePtr, projManagerPtr);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackDemoBasic::Init()
{

}

/// <summary>
/// 更新処理
/// </summary>
void PlayerAttackDemoBasic::Update() {}

/// <summary>
/// リセット
/// </summary>
void PlayerAttackDemoBasic::Reset() {}

/// <summary>
/// 攻撃処理
/// </summary>
void PlayerAttackDemoBasic::IsAttack() 
{
  if (projManager_) {
    projManager_->CreateProjectile(owner_->GetWorldPos(), owner_->GetDirection(), 1.0f * 60.0f);
  }
}
