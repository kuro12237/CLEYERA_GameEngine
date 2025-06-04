#include "PlayerBulletManager.h"

/// <summary>
/// 初期化処理
/// </summary>
void PlayerBulletManager::Init() {}

/// <summary>
/// 更新処理
/// </summary>
void PlayerBulletManager::Update() {
  // イテレータを使った安全なループ中削除
  for (auto it = bullets_.begin(); it != bullets_.end();) {

    // 更新処理
    (*it)->Update();

    // 非アクティブなら削除し、次の有効なイテレータを取得
    if (!(*it)->IsActive()) {
      it = bullets_.erase(it);
    } else {
      ++it; // アクティブなら次の要素へ
    }
  }
}

/// <summary>
/// 新しいBulletを追加
/// </summary>
void PlayerBulletManager::PushbackNewBullet(std::shared_ptr<IPlayerBullet> newBul) {
  if (newBul) {
    bullets_.push_back(std::move(newBul));
  }
}

/// <summary>
/// ImGuiの描画
/// </summary>
void PlayerBulletManager::DrawImGui() {
  //if (ImGui::TreeNode("ProjectileManager")) {

  //  size_t count = bullets_.size();
  //  ImGui::Text("Projectile Count = %d", count);
  //  ImGui::TreePop();
  //}
}