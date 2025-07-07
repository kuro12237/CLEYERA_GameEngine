#include "NormalEnemyIsCool.h"

#include "CLEYERA.h"
#include "Enemy/Normal/BaseNormalEnemy.h"

EnemyNodeState NormalEnemyIsNotCool::Execute(BaseNormalEnemy *baseNormalEnemy) {
    
    //クールタイム中ではない時通す
    if (baseNormalEnemy->GetIsCoolTime()!=false) {
        return EnemyNodeState::Success;
    } 
    else {
        return EnemyNodeState::Failure;
    }
}
