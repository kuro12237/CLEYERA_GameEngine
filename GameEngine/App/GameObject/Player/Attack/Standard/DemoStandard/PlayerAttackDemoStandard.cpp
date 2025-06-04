#include "PlayerAttackDemoStandard.h"
#include "../../../Bullet/Manager/PlayerBulletManager.h"
#include "../../../Core/playerCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoStandard::PlayerAttackDemoStandard(PlayerCore *corePtr,
                                                   PlayerBulletManager *bulManagerPtr) {
  IMagicAttack::SetPre(corePtr, bulManagerPtr);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackDemoStandard::Init() {};

/// <summary>
/// 更新処理
/// </summary>
void PlayerAttackDemoStandard::Update() {}

/// <summary>
/// リセット
/// </summary>
void PlayerAttackDemoStandard::Reset() {}

/// <summary>
/// 攻撃処理
/// </summary>
void PlayerAttackDemoStandard::IsAttack() {
  if (bulManager_) {

    // Bullet生成
    auto newBul = std::make_shared<PlayerDemoBullet>();
    // 数値の設定
    newBul->SetPosition(owner_->GetWorldPos());
    newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{0.0f, 0.0f, 1.0f}));
    // 初期化処理
    newBul->Init();
    // Managerに追加
    bulManager_->PushbackNewBullet(std::move(newBul));
  }
}
