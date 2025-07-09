#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"


NormalEnemyAttack::NormalEnemyAttack(const uint32_t & bulletType, const uint32_t & bulletNumber, const float_t & generateInterval) {
    this->bulletType_ = bulletType;
    this->bulletNumber_ = bulletNumber;
    this->generateInterval_ = generateInterval;
}

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy *baseNormalEnemy) {

    //生成終了
    if ( generatedNumber_ > bulletNumber_ ) {
        if ( baseNormalEnemy->GetIsCoolTime() == false ) {
            generatedNumber_ = 0u;
            return EnemyNodeState::Running;
        }

        //一旦クールタイム
        baseNormalEnemy->SetIsCoolTime(true);
        return EnemyNodeState::Success;
    }
    else {
        //弾を生成
        if ( baseNormalEnemy->GetIsCoolTime() == false ) {
            generateTime_ += DELTA_TIME_;
            if ( generateTime_ > generateInterval_ ) {
                baseNormalEnemy->GenerateBullet(bulletType_);
                generateTime_ = 0.0f;
                ++generatedNumber_;
            }
        }
    }
    

    //実行中
    return EnemyNodeState::Running;
}
