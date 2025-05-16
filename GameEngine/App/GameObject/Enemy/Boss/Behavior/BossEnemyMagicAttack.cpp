#include "BossEnemyMagicAttack.h"

#include "Enemy/Boss/BaseBossEnemy.h"

EnemyNodeState BossEnemyMagicAttack::Execute(BaseBossEnemy * baseBossEnemy){
#ifdef _DEBUG
	ImGui::Begin("Magic");
	ImGui::End();
#endif // _DEBUG
	//魔法攻撃
	baseBossEnemy;
	return EnemyNodeState::Success;
}
