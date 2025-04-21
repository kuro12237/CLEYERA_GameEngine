#include "PlayerBulletManager.h"

void PlayerBulletManager::Init() {}

void PlayerBulletManager::Update() {

   for (auto it = bullets_.begin(); it != bullets_.end();) {
      (*it)->Update();

      // GetIsDeadFlag が true の弾丸を削除
      if ((*it)->GetIsDeadFlag()) {
         it = bullets_.erase(it);
      } else {
         ++it;
      }
   }
}

void PlayerBulletManager::PushBullet(std::shared_ptr<IPlayerBullet> b, const Math::Vector::Vec3 &pos) {

   num++;
   b->SetName("bullet" + std::to_string(num));
   b->Init();
   b->SetTranslate(pos);
   bullets_.push_back(b);
}
