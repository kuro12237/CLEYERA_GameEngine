#include "NormalEnemyIsPlayerInRange.h"

#include "CLEYERA.h"
#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsPlayerInRange::Execute(BaseNormalEnemy *baseNormalEnemy) {
    // 距離を求める
    float_t disttance = Math::Vector::Func::Length(baseNormalEnemy->GetWorldPosition() -
                                                   baseNormalEnemy->GetPlayerPosition());

    // 範囲内かつ攻撃中かどうか
    if ((disttance <= baseNormalEnemy->GetTrackingStartDistance() &&
         disttance > baseNormalEnemy->GetAttackStartDistance())) {
      
        return EnemyNodeState::Success;
    } 
    else {
        return EnemyNodeState::Failure;
    }
}
