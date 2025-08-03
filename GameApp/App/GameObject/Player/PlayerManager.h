#pragma once

#include "CLEYERA.h"

#include "Camera/PlayerCamera.h"
#include "Command/PlayerCommandHandler.h"
#include "Attack/Manager/PlayerBulletManager.h"
#include "Core/playerCore.h"

#include "Attack/Manager/PlayerBulletManager.h"

#include"Component/Hp/HealthComponent.h"


// 前方宣言
class ItemManager;
class EnemyManager;
class PlayerSkillUI_Manager;

/* Player関連の一元管理クラス */
class PlayerManager : public CLEYERA::Component::ManagerComponent {

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

  /// <summary>
  /// Ptrの設定
  /// </summary>
  void SetPtr(std::weak_ptr<ItemManager> itemMgr, std::weak_ptr<EnemyManager> enemyMgr, std::weak_ptr<PlayerSkillUI_Manager> skillMgr);

#pragma region Accessor

  // CoreのweakPtrの取得
  std::weak_ptr<PlayerCore> GetPlayerCore() const { return this->core_; }

  // HP
  const int32_t &GetHp() const { return hp_->GetHp(); }

   
#pragma endregion

private:
  // カメラ
  std::shared_ptr<PlayerCamera> camera_;

  // バレットマネージャー
  std::shared_ptr<PlayerBulletManager> bulletManager_;

  // コア
  std::weak_ptr<PlayerCore> core_;

  std::shared_ptr<HealthComponent> hp_ = nullptr;
};