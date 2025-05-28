#include "NormalEnemyIsPlayerInAttackRange.h"

#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsPlayerInAttackRangeAndIsAttack::Execute(BaseNormalEnemy *baseNormalEnemy) {
	//距離を求める
	float_t disttance = Math::Vector::Func::Length(baseNormalEnemy->GetWorldPosition() - baseNormalEnemy->GetPlayerPosition());
	
    //判定
    //攻撃範囲内にいるかどうか、攻撃中かどうか
    if (disttance < baseNormalEnemy->GetAttackStartDistance() ||
        baseNormalEnemy->GetIsAttack() == true) {
        return EnemyNodeState::Success;
    } 
    else {
      baseNormalEnemy->SetIsAttack(false);
        return EnemyNodeState::Failure;
    }
}
