#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "Enemy/Normal/Normal1/NormalEnemyBullet.h"


EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy * baseNormalEnemy){
    float_t distance = Math::Vector::Func::Length(baseNormalEnemy->GetWorldPosition() -
                                                  baseNormalEnemy->GetPlayerPosition());


    generateTime_ += (1.0f / 60.0f);
    if (isRelease_==false) {
      GenerateBullet();
      isRelease_ = true;
      generateTime_ = 0.0f;
    }

    distance;
    // 弾の更新
    for (const std::shared_ptr<NormalEnemy2Bullet> &bullet : bullets_) {
      bullet->SetNormalEnemyPosition(baseNormalEnemy->GetPlayerPosition());
      bullet->SetPlayerPosition(baseNormalEnemy->GetPlayerPosition());
      bullet->Update();
    }


    // 弾の削除
    bullets_.remove_if([](const auto &bullet) { return bullet->GetIsDelete(); });
    if (bullets_.size() == 0u) {
      baseNormalEnemy->SetIsAttack(false);
    } else {
      baseNormalEnemy->SetIsAttack(true);
    }

#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG

    return EnemyNodeState::Success;

    
}

void NormalEnemyAttack::DisplayImGui(){
    int32_t newSize = static_cast<int32_t>(bullets_.size());

    ImGui::Begin("NormalEnemyAttack"); 
    ImGui::Checkbox("isAttack", &isReadyForAttack_);
    ImGui::InputFloat("攻撃時間", &generateTime_);
    ImGui::InputInt("Number", &newSize);
    ImGui::End();
}

void NormalEnemyAttack::GenerateBullet(){
    //弾
     std::unique_ptr<NormalEnemy2Bullet> bullet = std::make_unique<NormalEnemy2Bullet>();
    bullet->Init();
    //挿入
    bullets_.push_back(std::move(bullet));
}
