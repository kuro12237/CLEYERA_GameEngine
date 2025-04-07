#include "ColliderSystem.h"

void CLEYERA::Manager::ColliderSystem::ImGuiUpdate() {

   ImGui::Begin("collisionManager");

   ImGui::Checkbox("LineDraw", &isLineDraw_);

   ImGui::End();

 for (auto itr = colliderList_.begin(); itr != colliderList_.end(); ++itr) {
      if (itr->expired()) {
         continue;
      }
      auto collider = itr->lock();

      RenderManager::GetInstance()->PushLine3d(collider->GetLine());
   }
}

void CLEYERA::Manager::ColliderSystem::Update() {
   // 当たり判定
   for (auto itr1 = this->colliderList_.begin(); itr1 != colliderList_.end(); ++itr1) {
      if (itr1->expired()) {
         continue;
      }
      auto collider1 = itr1->lock();

      for (auto itr2 = std::next(itr1); itr2 != colliderList_.end(); ++itr2) {
         if (itr2->expired()) {
            continue;
         }
         auto collider2 = itr2->lock();
         if (collider1 == collider2) {
            continue;
         }

         // もし当たっていたら
         using type = Util::Collider::ColliderType;

         // OBB同士の当たり判定
         if (collider1->GetColliderType() == type::OBB && collider2->GetColliderType() == type::OBB) {
            Util::Collider::system::OBB obbA = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(collider1)->GetOBB();
            Util::Collider::system::OBB obbB = std::dynamic_pointer_cast<Util::Collider::OBBCollider>(collider2)->GetOBB();

            if (Util::Collider::system::Func::OBBCheck(obbA, obbB)) {
               // 何か処理
               collider1->HitCall(*collider2);
               collider2->HitCall(*collider1);
              
               continue;
            }
         }
      }
   }

   for ( auto c : colliderList_ )
   {
      c.lock()->Update();
   }
}
