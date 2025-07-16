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
    //(*it)->Update();

    // 非アクティブなら削除し、次の有効なイテレータを取得
    if (!(*it)->IsActive()) {
      (*it)->SetMode(CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE);
      it = bullets_.erase(it);
    } else {
      ++it; // アクティブなら次の要素へ
    }
  }
}

/// <summary>
/// 新しいBulletを追加
/// </summary>
void PlayerBulletManager::PushbackNewBullet(
    const std::string &category, std::shared_ptr<IPlayerBullet> newBul) {
  if (newBul) {
    objectManager_->CreateObject<IPlayerBullet>(category,newBul);
    bullets_.push_back(std::move(newBul));
  }
}

/// <summary>
/// ImGuiの描画
/// </summary>
void PlayerBulletManager::ImGuiUpdate() {
  if (ImGui::TreeNode("BulletManager")) {

    size_t count = bullets_.size();
    ImGui::Text("Bullet Count = %d", count);
    ImGui::TreePop();
  }
}