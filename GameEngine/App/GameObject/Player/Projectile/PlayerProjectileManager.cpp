#include "PlayerProjectileManager.h"

/// <summary>
/// 新しいProjectileを生成
/// </summary>
std::weak_ptr<PlayerProjectile>
PlayerProjectileManager::CreateProjectile(const Math::Vector::Vec3 &pos,
                                          const Math::Vector::Vec3 &vel, float lifeTime) {
  std::shared_ptr<PlayerProjectile> newProj = std::make_shared<PlayerProjectile>();
  newProj->Init();
  newProj->SetPosition(pos);
  newProj->SetVelocity(vel);
  newProj->SetLifeTime(lifeTime);

  projectiles_.push_back(newProj);
  return newProj;
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerProjectileManager::Init() {}

/// <summary>
/// 更新処理
/// </summary>
void PlayerProjectileManager::Update() {
  // イテレータを使った安全なループ中削除
  for (auto it = projectiles_.begin(); it != projectiles_.end();) {

    // 更新処理
    (*it)->Update();

    // 非アクティブなら削除し、次の有効なイテレータを取得
    if (!(*it)->IsActive()) {
      it = projectiles_.erase(it);
    } else {
      ++it; // アクティブなら次の要素へ
    }
  }
}

/// <summary>
/// ImGuiの描画
/// </summary>
void PlayerProjectileManager::DrawImGui() {
  if (ImGui::TreeNode("ProjectileManager")) {

    size_t count = projectiles_.size();
    ImGui::Text("Projectile Count = %d", count);
    ImGui::TreePop();
  }
}