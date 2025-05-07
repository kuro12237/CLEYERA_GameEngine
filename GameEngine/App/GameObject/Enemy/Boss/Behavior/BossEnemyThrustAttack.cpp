#include "BossEnemyThrustAttack.h"

#include "Enemy/Boss/BaseBossEnemy.h"


NodeState BossEnemyThrustAttack::Execute(BaseBossEnemy * baseBossEnemy){
    baseBossEnemy;
    //突撃
#ifdef _DEBUG
    ImGui::Begin("Thrust");
    ImGui::End();
#endif // _DEBUG
    return NodeState::Success;
}
