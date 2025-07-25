#include "NormalEnemyIsPlayerInAttackRange.h"

#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsPlayerInAttackRange::Execute(BaseNormalEnemy *baseNormalEnemy) {
	//距離を求める
	float_t disttance = Math::Vector::Func::Length(baseNormalEnemy->GetPosition() - baseNormalEnemy->GetPlayerPosition());
	
    //判定
    //攻撃範囲内にいるかどうか
    if (disttance < baseNormalEnemy->GetAttackStartDistance()) {
          baseNormalEnemy->SetIsAttack(true);
        return EnemyNodeState::Success;
    } 
    else {
      baseNormalEnemy->SetIsAttack(false);
        return EnemyNodeState::Failure;
    }
}
