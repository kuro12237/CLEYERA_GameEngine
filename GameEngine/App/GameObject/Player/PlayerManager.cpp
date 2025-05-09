#include "PlayerManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerManager::Init()
{
	// クラス名
	ManagerCompornent::name_ = VAR_NAME(PlayerManager);

	// カメラ
	camera_ = std::make_shared<PlayerCamera>();
	ManagerCompornent::cameraCompornents_.push_back(camera_);

	// コア
	core_ = std::make_shared<PlayerCore>();
	ManagerCompornent::objComponents_.push_back(core_);

	// コマンドハンドラー
	commandHandler_ = std::make_unique<PlayerCommandHandler>(core_);

	// 初期化
	ManagerCompornent::ListInit();

	// ペアレント
	camera_->SetTarget(core_->GetTranslate());
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerManager::Update()
{
	// 更新
	ManagerCompornent::ListUpdate();
}
