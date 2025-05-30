#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "Enemy/Normal/Normal1/NormalEnemyBullet.h"


NormalEnemyAttack::NormalEnemyAttack(const uint32_t &bulletType) { 
    this->bulletType_ = bulletType;
}

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy *baseNormalEnemy) {

    //弾を生成
    generateTime_ += (1.0f / 60.0f);
    if (generateTime_ > 3.0f) {
      baseNormalEnemy->GenerateBullet(bulletType_);
      generateTime_ = 0.0f;
      //生成成功
      return EnemyNodeState::Success;
    }


#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG

    //実行中
    return EnemyNodeState::Running;

    
}

void NormalEnemyAttack::DisplayImGui(){
    ImGui::Begin("NormalEnemyAttack"); 
    ImGui::Checkbox("isAttack", &isReadyForAttack_);
    ImGui::InputFloat("AttackTime", &generateTime_);
    ImGui::End();
}
