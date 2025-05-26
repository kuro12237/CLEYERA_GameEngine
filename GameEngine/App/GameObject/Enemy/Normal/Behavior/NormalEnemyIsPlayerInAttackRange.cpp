#include "NormalEnemyIsPlayerInAttackRange.h"

#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsPlayerInAttackRange::Execute(BaseNormalEnemy *baseNormalEnemy) {
	//距離を求める
	float_t disttance = Math::Vector::Func::Length(baseNormalEnemy->GetPosition() - baseNormalEnemy->GetPlayerPosition());
	//判定
	return disttance < baseNormalEnemy->GetAttackStartDistance() ? EnemyNodeState::Success: EnemyNodeState::Failure;

}
