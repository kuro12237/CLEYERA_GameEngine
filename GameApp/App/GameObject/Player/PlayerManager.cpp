#include "PlayerManager.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerManager::PlayerManager(std::weak_ptr<ItemManager> itemMgr) {
  // クラス名
  ManagerComponent::name_ = VAR_NAME(PlayerManager);

  camera_ = std::make_shared<PlayerCamera>();
  bulletManager_ = std::make_shared<PlayerBulletManager>();

  core_ = objectManager_->CreateObject<PlayerCore>(
      "PlayerCore", std::make_shared<PlayerCore>(camera_, bulletManager_, itemMgr));

  hp_ = std::make_unique<HealthComponent>();
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerManager::Init() {

  // カメラ
  ManagerComponent::cameraComponents_.push_back(camera_);

  // バレットマネージャー
  this->childManagerComponents_.push_back(bulletManager_);

  // 初期化
  ManagerComponent::ListInit();

  // ペアレント
  camera_->SetTarget(core_.lock()->GetTranslate());

  // Hp
  hp_->SetName(VAR_NAME(PlayerCore));
  hp_->Init();

  // 関数セット
  core_.lock()->SetHpCalcfunc(
      [this](int32_t attackPower) { hp_->CalcHp(attackPower); });
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerManager::Update() {
  // 更新
  ManagerComponent::ListUpdate();


}

void PlayerManager::ImGuiUpdate() {

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    hp_->ImGuiUpdate();

    ImGui::TreePop();
  }
}
