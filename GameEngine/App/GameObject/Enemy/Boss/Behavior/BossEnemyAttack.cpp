#include "BossEnemyAttack.h"

#include <imgui.h>
#include "Enemy/Boss/BaseBossEnemy.h"



EnemyNodeState BossEnemyAttack::Execute(BaseBossEnemy *baseBossEnemy) {
    //生成
    if (hasAttacked_==false) {
        baseBossEnemy->GenerateBullet(bulletType_);
        hasAttacked_ = true;
        generateTime_ = 0.0f;
        return EnemyNodeState::Running; 
    }

    //3秒超えたら処理終了
    generateTime_ += DELTA_TIME_;
    if (generateTime_ > 3.0f) {
        hasAttacked_ = false;
        return EnemyNodeState::Success;
    }


    //実行中
    return EnemyNodeState::Running;
}

