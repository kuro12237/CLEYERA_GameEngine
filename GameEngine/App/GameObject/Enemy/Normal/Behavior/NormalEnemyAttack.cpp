#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "Enemy/Normal/Normal1/NormalEnemyBullet.h"


EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy * baseNormalEnemy){
  float_t distance = Math::Vector::Func::Length(baseNormalEnemy->GetPosition() -
                                                baseNormalEnemy->GetPlayerPosition());

  // 攻撃範囲内かつ前回の攻撃が完了していたら、新たな攻撃を準備
  if (distance < baseNormalEnemy->GetAttackStartDistance() && isAttackFinished_) {
    isReadyForAttack_ = true;
  }

  // 攻撃準備完了時、弾を生成し、フラグを更新
  if (isReadyForAttack_) {
    GenerateBullet();
    isReadyForAttack_ = false;
    isAttackFinished_ = false;
    baseNormalEnemy->SetIsAttack(true);
  }

  // 弾の更新
  for (const auto &bullet : bullets_) {
    bullet->SetNormalEnemyPosition(baseNormalEnemy->GetPlayerPosition());
    bullet->SetPlayerPosition(baseNormalEnemy->GetPlayerPosition());
    bullet->Update();
  }

  // 弾の削除
  bullets_.remove_if([](const auto &bullet) { return bullet->GetIsDelete(); });

#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG

// 弾がすべて消えたときに攻撃終了とみなす
    if (bullets_.empty()) {
      baseNormalEnemy->SetIsAttack(false);
      isAttackFinished_ = true; // ここ重要：次の攻撃を許可
      return EnemyNodeState::Success;
    } else {
      return EnemyNodeState::Running;
    }
}

void NormalEnemyAttack::DisplayImGui(){
    int32_t newSize = static_cast<int32_t>(bullets_.size());

    ImGui::Begin("NormalEnemyAttack"); 
    ImGui::Checkbox("isAttack", &isReadyForAttack_);
    ImGui::InputInt("Number", &newSize);
    ImGui::End();
}

void NormalEnemyAttack::GenerateBullet(){
    //弾
    std::unique_ptr<NormalEnemyBullet> bullet =std::make_unique<NormalEnemyBullet>();
    bullet->Init();
    //挿入
    bullets_.push_back(std::move(bullet));
}
