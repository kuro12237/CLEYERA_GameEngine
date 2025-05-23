#pragma once

#include "CLEYERA.h"

#include "Command/PlayerCommandHandler.h"
#include "Core/playerCore.h"
#include "Camera/PlayerCamera.h"

#include "Projectile/PlayerProjectileManager.h"


/* Player関連の一元管理クラス */
class PlayerManager : public CLEYERA::Component::ManagerCompornent {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;


#pragma region Accessor

	// CoreのweakPtrの取得
	std::weak_ptr<PlayerCore> GetPlayerCore() const {
		return this->core_;
	}

#pragma endregion


private:

	// カメラ
	std::shared_ptr<PlayerCamera> camera_;

	// コア
	std::shared_ptr<PlayerCore> core_;

	// コマンドハンドラー
	std::unique_ptr<PlayerCommandHandler> commandHandler_;

};