#include "PlayerHealth.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerHealth::PlayerHealth(PlayerCore *corePtr) { owner_ = corePtr; }

/// <summary>
/// 初期化処理
/// </summary>
void PlayerHealth::Init(float initHealth) { health_ = initHealth; }

/// <summary>
/// 更新処理
/// </summary>
void PlayerHealth::Update() {

#ifdef _DEBUG
  if (ImGui::TreeNode("PlayerHealth")) {
    ImGui::Text("Health = %.1f", health_);
    ImGui::TreePop();
  }
#endif // _DEBUG
}