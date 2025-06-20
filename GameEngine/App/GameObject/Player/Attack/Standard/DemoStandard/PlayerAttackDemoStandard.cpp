#include "PlayerAttackDemoStandard.h"
#include "../../../Attack/Manager/PlayerBulletManager.h"
#include "../../../Core/playerCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoStandard::PlayerAttackDemoStandard(PlayerCore *corePtr,
                                                   std::weak_ptr<PlayerBulletManager> bulManagerPtr) {
  IMagicAttack::SetPre(corePtr, bulManagerPtr);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackDemoStandard::Init() {
};

/// <summary>
/// 更新処理
/// </summary>
void PlayerAttackDemoStandard::Update() {
  if (!isShooting_)
    return;

  shotTimer_ += 1.0f; // 1フレーム進む

  if (shotTimer_ >= shotInterval_) {
    shotTimer_ = 0.0f;

    int columnIndex = shotIndex_ % shotsPerRow_; // 0=右,1=中,2=左の順でループ
    FireOneBullet(columnIndex);

    shotIndex_++;
    if (shotIndex_ >= shotsPerSequence_) {
      // 2回分撃ち終えたら終了
      isShooting_ = false;
    }
  }
}

/// <summary>
/// リセット
/// </summary>
void PlayerAttackDemoStandard::Reset() {
}

/// <summary>
/// 攻撃処理
/// </summary>
void PlayerAttackDemoStandard::IsAttack() {
  if (!isShooting_) {
    StartAttack();
  }
}

void PlayerAttackDemoStandard::StartAttack() {
  isShooting_ = true;
  shotIndex_ = 0;
  shotTimer_ = 0.0f;
}

void PlayerAttackDemoStandard::FireOneBullet(int columnIndex) {
  if (!bulletManager_.lock())
    return;

  std::string tag = VAR_NAME(PlayerDemoStandardBullet);

  char name[ 32 ];

  // プレイヤー正面基準の位置を取得
  auto basePos = owner_->GetWorldPos();
  auto forward = IMagicAttack::CalcVelocity(Math::Vector::Vec3{ 0.0f, 0.0f, 1.0f });
  auto right = Math::Vector::Func::Normalize(Math::Vector::Func::Cross({ 0, 1, 0 }, forward));

  // 三列の横オフセット(右→中央→左)
  float spacing = 3.0f; // 弾の横間隔(調整可)
  Math::Vector::Vec3 offset;
  switch ( columnIndex ) {
  case 0:
      offset = right * spacing;
      break; // 右
  case 1:
      offset = Math::Vector::Vec3{ 0, 0, 0 };
      break; // 中央
  case 2:
      offset = right * -spacing;
      break; // 左
  default:
      offset = Math::Vector::Vec3{ 0, 0, 0 };
      break;
  }

  if ( bulletCount_ == 0 ) {

      auto newBul = std::make_shared<PlayerDemoStandardBullet>();

      newBul->SetPosition(basePos + offset);
      newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{ 0.0f, 0.0f, 0.4f }));
      newBul->Init();
      newBul->SetName(tag);

      bulletManager_.lock()->PushbackNewBullet(std::move(newBul));
  }
  else {
      std::snprintf(name, sizeof(name), "PlayerDemoStandardBullet.%03zu", bulletCount_);

      auto newBul = std::make_shared<PlayerDemoStandardBullet>();

      newBul->SetPosition(basePos + offset);
      newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{ 0.0f, 0.0f, 0.4f }));
      newBul->Init();
      newBul->SetName(name);

      bulletManager_.lock()->PushbackNewBullet(std::move(newBul));
  }

  bulletCount_++;
}

