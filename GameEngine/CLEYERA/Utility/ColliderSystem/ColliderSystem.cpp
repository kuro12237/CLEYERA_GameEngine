#include "ColliderSystem.h"
#include "Compornent/ObjectCompornent.h"

void CLEYERA::Manager::ColliderSystem::ImGuiUpdate() {

  if (ImGui::Button("LineDraw")) {

    if (isLineDraw_) {

      for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr) {
        if (itr->expired()) {
          continue;
        }
        const auto &collider = itr->lock()->GetCollder().lock();

        RenderManager::GetInstance()->PushLine3d(collider->GetLine());
      }
      isLineDraw_ = false;
    } else {
      for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr) {
        if (itr->expired()) {
          continue;
        }
        const auto &collider = itr->lock()->GetCollder().lock();
        RenderManager::GetInstance()->PopLine3d(collider->GetLine());
      }
      isLineDraw_ = true;
    }
  }
}
void CLEYERA::Manager::ColliderSystem::Update() {

  for (auto it = objectList_.begin(); it != objectList_.end();) {
    if (!(*it).expired()) {
      ++it;
    } else {
      it = objectList_.erase(it);
    }
  }
  std::unique_ptr<Util::Collider::Octree> octree =
      std::make_unique<Util::Collider::Octree>();
  octree->Init();

  std::unordered_map<int, std::vector<std::weak_ptr<Util::Collider::Collider>>>
      octreeGroups;


  for (auto obj : objectList_) {
    auto collider = obj.lock()->GetCollder().lock();
    Math::Vector::Vec3 min, max;
  
    int morton = octree->GetMortonNumber(collider->GetCenter());
    if (morton != -1) {
      octreeGroups[morton].push_back(collider);
    }
  }

  using type = Util::Collider::ColliderType;

  for (auto &[morton, group] : octreeGroups) {
    for (size_t i = 0; i < group.size(); ++i) {
      for (size_t j = i + 1; j < group.size(); ++j) {

        Util::Collider::system::OBB obbA =
            std::dynamic_pointer_cast<Util::Collider::OBBCollider>(
                group[i].lock())
                ->GetOBB();
        Util::Collider::system::OBB obbB =
            std::dynamic_pointer_cast<Util::Collider::OBBCollider>(
                group[j].lock())
                ->GetOBB();

        // 判定
        if (Util::Collider::system::Func::OBBCheck(obbA, obbB)) {

          group[i].lock()->HitCall(group[j].lock().get());
          group[j].lock()->HitCall(group[i].lock().get());
        }
      }
    }
  }
  // 各コライダーの更新
  for (auto it = objectList_.begin(); it != objectList_.end();) {
    if (!(*it).expired()) {
      (*it).lock()->GetCollder().lock()->Update();
      ++it;
    }
  }
}
