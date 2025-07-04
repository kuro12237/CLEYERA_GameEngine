#include "NormalEnemyIsNotAttacking.h"

#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsNotAttacking::Execute(BaseNormalEnemy *baseNormalEnemy) {
  baseNormalEnemy;
	//攻撃していない時にtrueを返す
	 return EnemyNodeState::Success;
  
}
