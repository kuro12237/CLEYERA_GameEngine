#include "NormalEnemyAttack.h"

#include <imgui.h>

#include "Enemy/Normal/BaseNormalEnemy.h"


NormalEnemyAttack::NormalEnemyAttack(const uint32_t & bulletType, const uint32_t & bulletNumber, const float_t & generateInterval) {
    this->bulletType_ = bulletType;
    this->bulletNumber_ = bulletNumber;
    this->generateInterval_ = generateInterval;
}

EnemyNodeState NormalEnemyAttack::Execute(BaseNormalEnemy *baseNormalEnemy) {
    //弾を生成
    if ( baseNormalEnemy->GetIsCool() == false ) {
        
        //生成終了
        if ( baseNormalEnemy->GetGenerateBulletNumber() > bulletNumber_ ) {

            //一旦クールタイム
            baseNormalEnemy->SetIsCool(true);
            return EnemyNodeState::Success;
        }
        else {
            generateTime_ += DELTA_TIME_;
            if ( generateTime_ > generateInterval_ ) {
                baseNormalEnemy->GenerateBullet(bulletType_);
                generateTime_ = 0.0f;
                baseNormalEnemy->IncrementBulletNumber();
                
            }
        }
    }

    
    

    //実行中
    return EnemyNodeState::Running;
}
