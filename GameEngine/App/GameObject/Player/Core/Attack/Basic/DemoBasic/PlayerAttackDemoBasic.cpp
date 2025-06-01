#include "PlayerAttackDemoBasic.h"
#include "../../../playerCore.h"
#include "../../../../Bullet/Manager/PlayerBulletManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoBasic::PlayerAttackDemoBasic(PlayerCore* corePtr, PlayerBulletManager* projManagerPtr)
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
    projManager_->CreateProjectile(owner_->GetWorldPos(), Math::Vector::Vec3(0.0f, 0.0f, 1.0f), 1.0f * 60.0f);
  }
}
