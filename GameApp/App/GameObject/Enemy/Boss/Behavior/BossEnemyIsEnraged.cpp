#include "BossEnemyIsEnraged.h"

#include "Enemy/Boss/BaseBossEnemy.h"

bool BossEnemyIsEnraged::CheckCondition(BaseBossEnemy * baseBossEnemy){
    //最大体力の半分以下になったら発狂
    if ( baseBossEnemy->GetEnemyParameter().hp_ <= baseBossEnemy->GetEnemyParameter().maxHp_ / 2 ) {
        return true;
    }
    else {
        return false;
    }
}
