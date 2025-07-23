#include "BossEnemyIsPlayerInAttackRange.h"

#include "Enemy/Boss/BaseBossEnemy.h"

EnemyNodeState BossEnemyIsPlayerInAttackRange::Execute(BaseBossEnemy * baseBossEnemy){
    //距離を求める
    float_t disttance = Math::Vector::Func::Length(baseBossEnemy->GetPosition() - baseBossEnemy->GetPlayerPosition());

    //判定
    //攻撃範囲内にいるかどうか
    if ( disttance < baseBossEnemy->GetAttackStartDistance() ) {
        baseBossEnemy->SetIsAttack(true);
        return EnemyNodeState::Success;
    }
    else {
        baseBossEnemy->SetIsAttack(false);
        return EnemyNodeState::Failure;
    }
}
