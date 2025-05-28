#include "PlayerManager.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerManager::PlayerManager() {
  camera_ = std::make_shared<PlayerCamera>();
  core_ = std::make_shared<PlayerCore>();
  commandHandler_ = std::make_unique<PlayerCommandHandler>(core_);
  projectileManager_ = std::make_unique<PlayerProjectileManager>();
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

  // 発射物管理クラス
  projectileManager_->Init();

  // 初期化
  ManagerCompornent::ListInit();

  // ペアレント
  camera_->SetTarget(core_->GetTranslate());
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

  // 発射物管理クラス
  projectileManager_->Update();
}
