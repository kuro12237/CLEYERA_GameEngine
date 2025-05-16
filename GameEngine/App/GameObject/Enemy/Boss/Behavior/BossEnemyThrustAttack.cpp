#include "BossEnemyThrustAttack.h"

#include "Enemy/Boss/BaseBossEnemy.h"


EnemyNodeState BossEnemyThrustAttack::Execute(BaseBossEnemy * baseBossEnemy){
    baseBossEnemy;
    //突撃
#ifdef _DEBUG
    ImGui::Begin("Thrust");
    ImGui::End();
#endif // _DEBUG
    return EnemyNodeState::Success;
}
