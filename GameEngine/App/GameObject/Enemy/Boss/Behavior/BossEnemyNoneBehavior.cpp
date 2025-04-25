#include "BossEnemyNoneBehavior.h"
#include <pch/Pch.h>


BossEnemyNoneBehavior::BossEnemyNoneBehavior(){
	//状態名を記録
	conditionName_ = VAR_NAME(BossEnemyNoneBehavior);
}

NodeState BossEnemyNoneBehavior::Execute(BaseBossEnemy * baseBossEnemy){
	baseBossEnemy;
	//成功
	return NodeState::Success;
}
