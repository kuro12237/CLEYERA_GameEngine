#include "BaseBossEnemy.h"
#include "BakugekiSnipe/BakugekiSnipeBossEnemyBullet1.h"
#include "BakugekiSnipe/BakugekiSnipeBossEnemyBullet2.h"


void BaseBossEnemy::GenerateBullet(const uint32_t &selection) {
   //弾
    std::weak_ptr<BaseBossEnemyBullet> bullet;
    //タグ
    std::string tag = "";

    switch (selection) {
    case BossBulletType::BossBullet1:
        // 弾1
        tag = VAR_NAME(BakugekiSnipeBossEnemyBullet1);
        //生成
        bullet = objectManager_->CreateObject<BakugekiSnipeBossEnemyBullet1>(
            tag, std::make_shared<BakugekiSnipeBossEnemyBullet1>());
        bullet.lock()->Initialize(translate_, playerPosition_);
        // 挿入
        bullets_.push_back(std::move(bullet));
        // 連番
        bulletCount_++;

        break;

    case BossBulletType::BossBullet2:
        // 弾2
        tag = VAR_NAME(BakugekiSnipeBossEnemyBullet2);
        //生成
        bullet = objectManager_->CreateObject<BakugekiSnipeBossEnemyBullet2>(
            tag, std::make_shared<BakugekiSnipeBossEnemyBullet2>());
        bullet.lock()->Initialize(translate_, playerPosition_);
        // 挿入
        bullets_.push_back(std::move(bullet));

        // 連番
        bulletCount_++;

        break;
    }
}
