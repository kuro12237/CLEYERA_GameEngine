#include "BossEnemyAttack.h"
#include "Enemy/Boss/BaseBossEnemy.h"
#include <imgui.h>

EnemyNodeState BossEnemyAttack::Execute(BaseBossEnemy * baseBossEnemy){

    // 弾を生成
  generateTime_ += DELTA_TIME_;
  if (generateTime_ > 3.0f) {
    baseBossEnemy->GenerateBullet(bulletType_);
    generateTime_ = 0.0f;
    // 生成成功
    return EnemyNodeState::Success;
  }

  // 実行中
  return EnemyNodeState::Running;
}
