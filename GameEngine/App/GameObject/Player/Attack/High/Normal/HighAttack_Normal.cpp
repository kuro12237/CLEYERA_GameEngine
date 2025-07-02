#include "HighAttack_Normal.h"
#include "HighAttack_NormalBullet.h"
#include "../../../Core/playerCore.h"

HighAttack_Normal::HighAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
	lua_ = std::make_unique<LuaScript>();
}

void HighAttack_Normal::Init() 
{
	shotIndex_ = 0;         // 発射した弾のインデックス(0〜5)
	shotsPerSequence_ = 6;  // 合計発射数
	shotsPerRow_ = 3;       // 1列あたりの弾数（右・中・左）
	shotInterval_ = 5.0f; // 発射間隔（フレーム数）
	shotTimer_ = 0.0f;    // 発射タイマー
	isShooting_ = false; // 攻撃開始フラグ
    coolDownInterval_ = 2.0f * 60.0f; // 攻撃のインターバル
}


void HighAttack_Normal::Update()
{
    if ( isShooting_ ) {

        shotTimer_ += 1.0f; // 1フレーム進む

        if ( shotTimer_ >= shotInterval_ ) {
            shotTimer_ = 0.0f;

            int columnIndex = shotIndex_ % shotsPerRow_; // 0=右,1=中,2=左の順でループ
            FireOneBullet(columnIndex);

            shotIndex_++;
            if ( shotIndex_ >= shotsPerSequence_ ) {
                // 2回分撃ち終えたら終了
                isShooting_ = false;
                SetAttackCoolDown();
            }
        }
    }
    else {
        UpdateCoolDownTimer();
    }
}


void HighAttack_Normal::Reset() {}


void HighAttack_Normal::IsAttack()
{
    // 攻撃可能でなければ何もしない
    if ( IsCoolDown() )
        return;

    // 既に射撃中も何もしない
	if ( !isShooting_ ) {
		StartAttack();
    }
}


void HighAttack_Normal::DrwaImGui() {}


void HighAttack_Normal::StartAttack()
{
	isShooting_ = true;
	shotIndex_ = 0;
	shotTimer_ = 0.0f;
}


void HighAttack_Normal::FireOneBullet(int columnIndex)
{
    constexpr float kSpacing = 3.0f; // 弾の横間隔

    auto bulletManager = bulletManager_.lock();
    if ( !bulletManager )
        return;

    const std::string tagBase = VAR_NAME(HighAttack_NormalBullet);

    // プレイヤー正面基準の位置と方向
    const auto basePos = owner_->GetWorldPos();
    const auto forward = IMagicAttack::CalcVelocity({ 0.0f, 0.0f, 1.0f });
    const auto right = Math::Vector::Func::Normalize(Math::Vector::Func::Cross({ 0, 1, 0 }, forward));

    // 三列の横オフセット(右→中央→左)
    Math::Vector::Vec3 offset;
    switch ( columnIndex ) {
    case 0: offset = right * kSpacing; break;   // 右
    case 1: offset = { 0, 0, 0 }; break;        // 中央
    case 2: offset = right * -kSpacing; break;  // 左
    default: offset = { 0, 0, 0 }; break;
    }

    // bullet名生成
    std::string bulletName = GenerateBulletName(tagBase, bulletCount_);

    // bullet生成共通処理
    auto bullet = std::make_shared<HighAttack_NormalBullet>();
    bullet->SetPosition(basePos + offset);
    bullet->SetVelocity(IMagicAttack::CalcVelocity({ 0.0f, 0.0f, 0.4f }));
    bullet->Init();
    bullet->SetName(bulletName);

    bulletManager->PushbackNewBullet(std::move(bullet));

    bulletCount_++;
}

std::string HighAttack_Normal::GenerateBulletName(const std::string & baseTag, size_t count)
{
    if ( count == 0 )
        return baseTag;

    char name[ 32 ] = {};
    std::snprintf(name, sizeof(name), "%s.%03zu", baseTag.c_str(), count);
    return name;
}
