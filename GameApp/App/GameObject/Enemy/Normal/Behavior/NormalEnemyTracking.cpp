#include "NormalEnemyTracking.h"

#include "Enemy/Normal/BaseNormalEnemy.h"


EnemyNodeState NormalEnemyTracking::Execute(BaseNormalEnemy * baseNormalEnemy){

    //差分を求める
    Math::Vector::Vec3 difference = {
        .x = baseNormalEnemy->GetPlayerPosition().x - baseNormalEnemy->GetPosition().x,
        .y = 0.0f,
        .z = baseNormalEnemy->GetPlayerPosition().z - baseNormalEnemy->GetPosition().z,
    };
    
    //正規化し本体に設定
    baseNormalEnemy->SetDirection(Math::Vector::Func::Normalize(difference));
    

    //成功
    return EnemyNodeState::Success;
}
