#include "NormalEnemyIsNotAttacking.h"

#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsNotAttacking::Execute(BaseNormalEnemy *baseNormalEnemy) {
	//攻撃していない時にtrueを返す
	 return baseNormalEnemy->GetIsAttack() ? EnemyNodeState::Failure : EnemyNodeState::Success;
  
}
