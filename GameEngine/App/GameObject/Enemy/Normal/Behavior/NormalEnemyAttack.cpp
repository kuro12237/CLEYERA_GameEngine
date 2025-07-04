#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"


NormalEnemyAttack::NormalEnemyAttack(const uint32_t &bulletType) { 
    this->bulletType_ = bulletType;
}

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy *baseNormalEnemy) {

    //弾を生成
    generateTime_ += DELTA_TIME_;
    if (generateTime_ > 3.0f) {
      baseNormalEnemy->GenerateBullet(bulletType_);
      generateTime_ = 0.0f;
      //生成成功
      return EnemyNodeState::Success;
    }

    //実行中
    return EnemyNodeState::Running;
}
