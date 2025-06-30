#include "BossEnemyAttack.h"

#include <imgui.h>
#include "Enemy/Boss/BaseBossEnemy.h"



EnemyNodeState BossEnemyAttack::Execute(BaseBossEnemy *baseBossEnemy) {
  if (!hasAttacked_) {
    baseBossEnemy->GenerateBullet(bulletType_);
    hasAttacked_ = true;
    generateTime_ = 0.0f;
    return EnemyNodeState::Running; // 実行中
  }


  generateTime_ += DELTA_TIME_;
  if (generateTime_ > 3.0f) {
    hasAttacked_ = false;
    return EnemyNodeState::Success;
  }


    //実行中
    return EnemyNodeState::Running;
}

