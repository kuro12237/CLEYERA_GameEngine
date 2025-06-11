#pragma once

#include "CLEYERA.h"

#include "Camera/PlayerCamera.h"
#include "Command/PlayerCommandHandler.h"
#include "Core/playerCore.h"

#include "Bullet/Manager/PlayerBulletManager.h"

#include"Component/Hp/HealthComponent.h"


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

  void ImGuiUpdate() override;

#pragma region Accessor

  // CoreのweakPtrの取得
  std::weak_ptr<PlayerCore> GetPlayerCore() const { return this->core_; }

  
    const int32_t &GetHp() const { return hp_->GetHp(); }

#pragma endregion

private:
  // カメラ
  std::shared_ptr<PlayerCamera> camera_;

  // コア
  std::shared_ptr<PlayerCore> core_;

  // コマンドハンドラー
  std::unique_ptr<PlayerCommandHandler> commandHandler_;

  // 発射物管理クラス
  std::shared_ptr<PlayerBulletManager> projectileManager_;

  std::unique_ptr<HealthComponent> hp_ = nullptr;
};