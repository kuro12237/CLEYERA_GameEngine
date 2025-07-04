#include "BossEnemyIsPlayerInRange.h"

#include "CLEYERA.h"
#include "Enemy/Boss/BaseBossEnemy.h"

bool BossEnemyIsPlayerInRange::CheckCondition(BaseBossEnemy * baseBossEnemy){

    //プレイヤーの座標
    Math::Vector::Vec3 playerPosition = baseBossEnemy->GetPlayerPosition();
    //本体の座標
    Math::Vector::Vec3 bossEnemyPosition = baseBossEnemy->GetPosition();
    //Y軸成分を無くす
    playerPosition.y = 0.0f;
    bossEnemyPosition.y = 0.0f;

    //距離を計算
    float_t distance = Math::Vector::Func::Length(playerPosition- bossEnemyPosition);

    //判定
    if ( distance <= range_ ) {
        return true;
    }
    else {
        return false;
    }

}
