#include "NormalEnemyTracking.h"

#include "Enemy/Normal/BaseNormalEnemy.h"


EnemyNodeState NormalEnemyTracking::Execute(BaseNormalEnemy * baseNormalEnemy){

    //方向を求める
    Math::Vector::Vec3 velocity = {
        .x = baseNormalEnemy->GetPlayerPosition().x - baseNormalEnemy->GetPosition().x,
        .y = 0.0f,
        .z = baseNormalEnemy->GetPlayerPosition().z - baseNormalEnemy->GetPosition().z,

    };

    //本体に設定
    baseNormalEnemy->SetVelocity(Math::Vector::Func::Normalize(velocity));
    
    //成功
    return EnemyNodeState::Success;
}
