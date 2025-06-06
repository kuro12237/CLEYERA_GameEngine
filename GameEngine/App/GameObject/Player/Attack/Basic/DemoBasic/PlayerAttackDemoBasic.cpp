#include "PlayerAttackDemoBasic.h"
#include "../../../Bullet/Manager/PlayerBulletManager.h"
#include "../../../Core/playerCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoBasic::PlayerAttackDemoBasic(PlayerCore *corePtr,
                                             PlayerBulletManager *bulManagerPtr) {
  // Ptrの設定
  IMagicAttack::SetPre(corePtr, bulManagerPtr);
  lua_ = std::make_unique<LuaScript>();
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackDemoBasic::Init() {

  // 読み込み
  lua_->LoadScript("Player/Attack/DemoBasic", "PlayerDemoAttackPram");
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerAttackDemoBasic::Update() {

  // タイマー進行
  if (comboTimer_ > 0.0f) {
    comboTimer_--;

    // リセット
    if (comboTimer_ <= 0.0f) {
      comboStep_ = 0;
      comboTimer_ = 0.0f;
    }
  }
}

/// <summary>
/// リセット
/// </summary>
void PlayerAttackDemoBasic::Reset() {}

/// <summary>
/// 攻撃処理
/// </summary>
void PlayerAttackDemoBasic::IsAttack() {

  // 弾を生成
  FireBullet();

  // コンボ進行
  comboStep_ = (comboStep_ + 1) % maxCombo_;
  comboTimer_ = comboInterval_;
}

/// <summary>
/// Bulletを生成
/// </summary>
void PlayerAttackDemoBasic::FireBullet() {
  if (bulManager_) {
    // Bullet生成
    auto newBul = std::make_shared<PlayerDemoBullet>();
    // 数値の設定
    newBul->SetPosition(owner_->GetWorldPos());
    newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{0.0f, 0.0f, 20.0f}));
    newBul->SetParams(GetBulletParams());
    // 初期化処理
    newBul->Init();
    // Managerに追加
    bulManager_->PushbackNewBullet(std::move(newBul));
  }
}

/// <summary>
/// Bulletのパラメータの取得
/// </summary>
PlayerDemoBullet::BulletCurveParams PlayerAttackDemoBasic::GetBulletParams() {

    PlayerDemoBullet::BulletCurveParams result{};
  switch (comboStep_) {
  case 0:
    result.horizontalCurve = 3.0f;
    break;

  case 1:
    result.horizontalCurve = -3.0f;
    break;

  case 2:
    break;

  default:
    break;
  }

  return result;
}

/// <summary>
/// ImGuiの描画
/// </summary>
void PlayerAttackDemoBasic::DrwaImGui() {
  if (ImGui::TreeNode("DemoBasic")) {

    ImGui::Text("ComboStep : %d", comboStep_);
    ImGui::TreePop();
  }
}