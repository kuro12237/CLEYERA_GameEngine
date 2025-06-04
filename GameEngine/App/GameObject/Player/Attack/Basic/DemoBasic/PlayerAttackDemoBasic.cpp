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
    newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{0.0f, 0.0f, 1.0f}));
    newBul->SetParam(GetBulletParam());
    // 初期化処理
    newBul->Init();
    // Managerに追加
    bulManager_->PushbackNewBullet(std::move(newBul));
  }
}

/// <summary>
/// パラメーターの取得
/// </summary>
PlayerDemoBulletParam PlayerAttackDemoBasic::GetBulletParam() {
  PlayerDemoBulletParam result{};

  if (comboStep_ == 0) {
    result.horizontalCurve = 0.5f;
    result.verticalCurve = 0.0f;
    result.curveDistance = 5.0f;
    result.useDistance = true;
    result.curveTime = 1.0f;
    result.type = PlayerDemoBulletParam::CurveType::SinWave;
  } else if (comboStep_ == 1) {
    result.horizontalCurve = -0.5f;
    result.verticalCurve = 0.0f;
    result.curveDistance = 5.0f;
    result.useDistance = true;
    result.curveTime = 1.0f;
    result.type = PlayerDemoBulletParam::CurveType::Linear;
  } else if (comboStep_ == 2) {
    result.horizontalCurve = 0.0f;
    result.verticalCurve = 0.3f;
    result.curveDistance = 4.0f;
    result.useDistance = true;
    result.curveTime = 1.0f;
    result.type = PlayerDemoBulletParam::CurveType::EaseInOut;
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