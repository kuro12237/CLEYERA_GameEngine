#include "NormalEnemyIsPlayerInRange.h"

#include "CLEYERA.h"
#include "Enemy/Normal/BaseNormalEnemy.h"

bool NormalEnemyIsPlayerInRange::CheckCondition(BaseNormalEnemy * baseNormalEnemy){

    if (baseNormalEnemy->GetIsAttack()==true) {
    return true; // 攻撃中なら無条件で進める
  }

    //プレイヤーの座標
    Math::Vector::Vec3 playerPosition = baseNormalEnemy->GetPlayerPosition();
    //本体の座標
    Math::Vector::Vec3 bossEnemyPosition = baseNormalEnemy->GetPosition();
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
