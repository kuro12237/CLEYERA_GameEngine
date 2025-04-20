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
   // Octree を初期化
   octree_ = std::make_unique<Util::Collider::Octree>();

   // Collider を Octree に登録
   for (auto c : colliderList_) {
      if (!c.expired()) {
         octree_->Insert(c);
      }
   }

   using type = Util::Collider::ColliderType;

   // 衝突判定
   for (auto &c : colliderList_) {
      if (c.expired())
         continue;
      auto collider = c.lock();

      // 範囲検索（中心点の周囲に存在するコライダーを取得）
      Math::Vector::Vec3 center = collider->GetCenter();
      float range = 320.0f; // 判定に使う半径。適宜調整
      Math::Vector::Vec3 min = center - Math::Vector::Vec3(range,range,range);
      Math::Vector::Vec3 max = center + Math::Vector::Vec3(range,range,range);

      auto candidates = octree_->Query(min, max);

      for (const auto &other : candidates) {
         if (collider == other.lock())
            continue;

         if (collider->GetColliderType() == type::OBB && other.lock()->GetColliderType() == type::OBB) {

            Util::Collider::system::OBB obbA = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(collider)->GetOBB();
            Util::Collider::system::OBB obbB = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(other.lock())->GetOBB();

            if (Util::Collider::system::Func::OBBCheck(obbA, obbB)) {
               //collider->HitCall(*other.lock());
               other.lock()->HitCall(*collider);

               std::string message = "Failed open data file for write.";
               MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
            }
         }
      }
   }

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
