#include "NormalEnemyTracking.h"

#include "Enemy/Normal/BaseNormalEnemy.h"


EnemyNodeState NormalEnemyTracking::Execute(BaseNormalEnemy * baseNormalEnemy){

    //方向を求める
    Math::Vector::Vec3 velocity = {
        .x = baseNormalEnemy->GetPlayerPosition().x - baseNormalEnemy->GetWorldPosition().x,
        .y = 0.0f,
        .z = baseNormalEnemy->GetPlayerPosition().z - baseNormalEnemy->GetWorldPosition().z,

    };

    const float_t SPEED = 0.1f;
    //本体に設定
    baseNormalEnemy->SetVelocity(Math::Vector::Func::Normalize(velocity) * SPEED);
    
    //成功
    return EnemyNodeState::Success;
}
