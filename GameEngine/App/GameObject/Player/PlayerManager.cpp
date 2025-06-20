#include "PlayerManager.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerManager::PlayerManager() {
  camera_ = std::make_shared<PlayerCamera>();
  core_ = std::make_shared<PlayerCore>();
  commandHandler_ = std::make_unique<PlayerCommandHandler>(core_);
  bulletManager_ = std::make_shared<PlayerBulletManager>();
  hp_ = std::make_unique<HealthComponent>();
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerManager::Init() {
  // クラス名
  ManagerCompornent::name_ = VAR_NAME(PlayerManager);

  // カメラ
  ManagerCompornent::cameraCompornents_.push_back(camera_);

  // コア
  core_->SetCameraPtr(camera_);
  core_->Init();
  ManagerCompornent::objComponents_.push_back(core_);
  
  // コマンドハンドラー
  commandHandler_->Init();
  
  // バレットマネージャー
  this->childManagerComponents_.push_back(bulletManager_);

  // 初期化
  ManagerCompornent::ListInit();

  // ペアレント
  camera_->SetTarget(core_->GetTranslate());

  // Hp
  hp_->SetName(VAR_NAME(PlayerCore));
  hp_->Init();

  //関数セット
  core_->SetHpCalcfunc([this](int32_t attackPower) { hp_->CalcHp(attackPower); });

}

/// <summary>
/// 更新処理
/// </summary>
void PlayerManager::Update() {
  // 更新
  ManagerCompornent::ListUpdate();

  // ハンドラー
  commandHandler_->Handle();
  commandHandler_->Exec();

}

void PlayerManager::ImGuiUpdate() {

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    for (auto obj : objComponents_) {

      obj.lock()->ImGuiUpdate();
    }
    for (auto obj : cameraCompornents_) {
      obj.lock()->ImGuiUpdate();
    }

    hp_->ImGuiUpdate();

    ImGui::TreePop();
  }
}
