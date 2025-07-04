#include "IPlayerBullet.h"
#include "../../Core/playerCore.h"

void IPlayerBullet::OnCollision(std::weak_ptr<ObjectComponent> other) {

  auto obj = other.lock();
  // Player型にキャストできるかをチェック
  if (auto p = std::dynamic_pointer_cast<PlayerCore>(obj)) {
    return;
  }
  if (auto p = std::dynamic_pointer_cast<IPlayerBullet>(obj)) {
    return;
  }

  isActive_ = false;
}
