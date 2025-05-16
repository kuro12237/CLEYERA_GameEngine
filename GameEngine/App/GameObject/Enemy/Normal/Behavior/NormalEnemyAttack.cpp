#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "Enemy/Normal/Normal1/NormalEnemyBullet.h"

NormalEnemyAttack::NormalEnemyAttack() {

}

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy * baseNormalEnemy){

    //時間変化
    if (isAttack_ == true ) {
        //弾を生成
        GenerateBullet();
        isAttack_ = false;
    }

    //弾の更新
    for (const auto & bullet : bullets_ ) {
        //雑魚敵の座標を設定
        bullet->SetNormalEnemyPosition(baseNormalEnemy->GetPlayerPosition());
        //プレイヤーの座標を設定
        bullet->SetPlayerPosition(baseNormalEnemy->GetPlayerPosition());
        //更新
        bullet->Update();
    }

    //isDeleteがtrueになったら消す
    bullets_.remove_if([=](const auto & bullet) {
        return bullet->GetIsDelete();
    });

#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG


    // 攻撃中か終了したかを判断
    if ( !bullets_.empty() ) {
        return EnemyNodeState::Running;  // 弾が残ってる → 攻撃中
    }
    else {
        return EnemyNodeState::Success;  // 弾が全部消えた → 攻撃終了
    }
    
}

void NormalEnemyAttack::DisplayImGui(){
    int32_t newSize = static_cast<int32_t>(bullets_.size());

    ImGui::Begin("NormalEnemyAttack"); 
    ImGui::Checkbox("isAttack", &isAttack_);
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
