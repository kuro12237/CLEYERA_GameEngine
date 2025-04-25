#include "BossEnemyTracking.h"

#include "Enemy/Boss/BaseBossEnemy.h"

BossEnemyTracking::BossEnemyTracking(){
    //状態名を記録
    conditionName_ = VAR_NAME(BossEnemyTracking);

    
}

NodeState BossEnemyTracking::Execute(BaseBossEnemy * baseBossEnemy){

    //方向を求める
    Math::Vector::Vec3 velocity = {
        .x = baseBossEnemy->GetPlayerPosition().x - baseBossEnemy->GetPosition().x,
        .y = 0.0f,
        .z = baseBossEnemy->GetPlayerPosition().z - baseBossEnemy->GetPosition().z,

    };

    //本体に設定
    baseBossEnemy->SetVelocity(Math::Vector::Func::Normalize(velocity));
    
    //成功
    return NodeState::Success;

    
}
