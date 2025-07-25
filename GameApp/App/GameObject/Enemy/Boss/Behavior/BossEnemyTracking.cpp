#include "BossEnemyTracking.h"

#include "Enemy/Boss/BaseBossEnemy.h"


EnemyNodeState BossEnemyTracking::Execute(BaseBossEnemy * baseBossEnemy){

    //方向を求める
    Math::Vector::Vec3 velocity = {
        .x = baseBossEnemy->GetPlayerPosition().x - baseBossEnemy->GetPosition().x,
        .y = 0.0f,
        .z = baseBossEnemy->GetPlayerPosition().z - baseBossEnemy->GetPosition().z,

    };

    //正規化し本体に設定
    baseBossEnemy->SetDirection(Math::Vector::Func::Normalize(velocity));

    //成功
    return EnemyNodeState::Success;

    
}
