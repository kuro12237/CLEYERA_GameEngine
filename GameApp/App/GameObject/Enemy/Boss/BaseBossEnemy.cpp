#include "BaseBossEnemy.h"
#include "First/BakugekiSnipeBossEnemyBullet1.h"
#include "First/BakugekiSnipeBossEnemyBullet2.h"


void BaseBossEnemy::GenerateBullet(const uint32_t &selection) {
  std::shared_ptr<BaseBossEnemyBullet> bullet = nullptr;

  switch (selection) {
  case BossBulletType::BossBullet1:
    // 弾1
    bullet = std::make_shared<BakugekiSnipeBossEnemyBullet1>();
    bullet->Initialize(translate_, playerPosition_);
    // 挿入
    bullets_.push_back(std::move(bullet));

    break;

  case BossBulletType::BossBullet2:
    // 弾2
    bullet = std::make_shared<BakugekiSnipeBossEnemyBullet2>();
    bullet->Initialize(translate_, playerPosition_);
    // 挿入
    bullets_.push_back(std::move(bullet));

    break;
  }
}
