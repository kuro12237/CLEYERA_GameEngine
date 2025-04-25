#include "PlayerManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerManager::Init()
{
	// クラス名
	ManagerCompornent::name_ = VAR_NAME(PlayerManager);

	// コア
	core_ = std::make_shared<PlayerCore>();
	ManagerCompornent::objComponents_.push_back(core_);



	// 初期化
	ManagerCompornent::ListInit();
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerManager::Update()
{
}
