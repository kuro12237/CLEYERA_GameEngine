#include "ColliderSystem.h"

void CLEYERA::Manager::ColliderSystem::ImGuiUpdate() {

   ImGui::Begin("collisionManager");

   ImGui::End();

   if (ImGui::Button("LineDraw")) {

      if (isLineDraw_) {

         for (auto itr = colliderList_.begin(); itr != colliderList_.end(); ++itr) {
            if (itr->expired()) {
               continue;
            }
            auto collider = itr->lock();

            RenderManager::GetInstance()->PushLine3d(collider->GetLine());
         }
         isLineDraw_ = false;
      } else {
         for (auto itr = colliderList_.begin(); itr != colliderList_.end(); ++itr) {
            if (itr->expired()) {
               continue;
            }
            auto collider = itr->lock();
            RenderManager::GetInstance()->PopLine3d(collider->GetLine());
         }
         isLineDraw_ = true;
      }
   }
}
void CLEYERA::Manager::ColliderSystem::Update() {

   std::unique_ptr<Util::Collider::OctreeSpaceDivision> octree = std::make_unique<Util::Collider::OctreeSpaceDivision>();
   octree->Init();

   std::unordered_map<int, std::vector<std::weak_ptr<Util::Collider::Collider>>> octreeGroups;

   for (auto obj : colliderList_) {
      int morton = octree->GetMortonNumber(obj.lock()->GetCenter());
      if (morton != -1) {
         octreeGroups[morton].push_back(obj);
      }
   }

   using type = Util::Collider::ColliderType;

   for (auto &[morton, group] : octreeGroups) {
      for (size_t i = 0; i < group.size(); ++i) {
         for (size_t j = i + 1; j < group.size(); ++j) {

            Util::Collider::system::OBB obbA = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(group[i].lock())->GetOBB();
            Util::Collider::system::OBB obbB = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(group[j].lock())->GetOBB();

            if (Util::Collider::system::Func::OBBCheck(obbA, obbB)) {
         
               group[i].lock()->HitCall(group[j].lock().get());
               group[j].lock()->HitCall(group[i].lock().get());


               std::string message = "Failed open data file for write.";
               MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
            }
         }
      }
   }

   //// 衝突判定
   //for (auto &c : colliderList_) {
   //   if (c.expired())
   //      continue;
   //   auto collider = c.lock();

   //   // 範囲検索（中心点の周囲に存在するコライダーを取得）
   //   Math::Vector::Vec3 center = collider->GetCenter();
   //   float range = 320.0f; // 判定に使う半径。適宜調整
   //   Math::Vector::Vec3 min = center - Math::Vector::Vec3(range, range, range);
   //   Math::Vector::Vec3 max = center + Math::Vector::Vec3(range, range, range);

   //   auto candidates = colliderList_;

   //   for (const auto &other : candidates) {
   //      if (collider == other.lock())
   //         continue;

   //      if (collider->GetColliderType() == type::OBB && other.lock()->GetColliderType() == type::OBB) {

   //         Util::Collider::system::OBB obbA = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(collider)->GetOBB();
   //         Util::Collider::system::OBB obbB = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(other.lock())->GetOBB();

   //         if (Util::Collider::system::Func::OBBCheck(obbA, obbB)) {
   //            // collider->HitCall(*other.lock());
   //            other.lock()->HitCall(*collider);

   //            std::string message = "Failed open data file for write.";
   //            MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
   //         }
   //      }
   //   }
   //}

   // 各コライダーの更新
   for (auto it = colliderList_.begin(); it != colliderList_.end();) {
      if (!(*it).expired()) {
         (*it).lock()->Update();
         ++it;
      } else {
         it = colliderList_.erase(it);
      }
   }
}
