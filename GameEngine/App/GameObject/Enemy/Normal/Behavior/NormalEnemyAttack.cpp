#include "NormalEnemyAttack.h"

#include <imgui.h>

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy * baseBossEnemy){

#ifdef _DEBUG
    ImGui::Begin("Attack");
    ImGui::End();
#endif // _DEBUG
    baseBossEnemy;

    //成功
    return EnemyNodeState::Success;
}
