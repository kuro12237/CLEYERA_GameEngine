#include "BossEnemyAttack.h"
#include <imgui.h>

NodeState BossEnemyAttack::Execute(BaseBossEnemy * baseBossEnemy){

#ifdef _DEBUG
    ImGui::Begin("Attack");
    ImGui::End();
#endif // _DEBUG
    baseBossEnemy;

    //成功
    return NodeState::Success;
}
