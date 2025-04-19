#include "PlayerActionCommand.h"

void PlayerActionCommand::Exec(const std::list<std::weak_ptr<IPlayer>> &p) {
   // 場所入手
   Math::Vector::Vec3 pos = {};
   for (auto obj : p) {

      if (auto it = dynamic_cast<PlayerCore *>(obj.lock().get())) {
         pos = it->GetTranslate();
      }
   }
   // 発射
   for (auto obj : p) {
      if (auto it = dynamic_cast<PlayerBulletManager *>(obj.lock().get())) {
          //クラス名ヲ別の物にすると他の弾クラスの物が作られる
         it->PushBullet(std::make_shared<PlayerBullet>(), pos);
      }
   }
}
