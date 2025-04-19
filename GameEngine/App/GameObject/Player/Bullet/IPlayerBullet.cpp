#include "IPlayerBullet.h"

void IPlayerBullet::CalcAliveTimer() {

   timer_ += CalcDeltaTime(flame_);

   if (timer_ >= maxTimer_) {

      isDeadFlag_ = true;
   }
}
