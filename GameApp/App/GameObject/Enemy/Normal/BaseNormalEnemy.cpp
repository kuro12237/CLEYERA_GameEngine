#include "BaseNormalEnemy.h"

#include "Cannon/CannonNormalEnemy1Bullet.h"
#include "Gun/GunNormalEnemyBullet.h"
#include "Stalker/StalkerEnemyBullet.h"
#include "Donut/DonutNormalEnemyBullet.h"

#include <Player/PlayerManager.h>

Math::Vector::Vec3 BaseNormalEnemy::GetPlayerPosition(){
    return playerManager_->GetPlayerCore().lock()->GetWorldPos();
}

void BaseNormalEnemy::GenerateBullet(const uint32_t &selection) {
  std::weak_ptr<BaseNormalEnemyBullet> bullet;

  std::string tag = "";

  Math::Vector::Vec3 playerPosition = playerManager_->GetPlayerCore().lock()->GetWorldPos();


  switch (selection) {
  case BulletType::CannonBullet:
    // 弾1
    tag = VAR_NAME(CannonNormalEnemy1Bullet);
    bullet = objectManager_->CreateObject<CannonNormalEnemy1Bullet>(
        tag, std::make_shared<CannonNormalEnemy1Bullet>());

    bullet.lock()->Initialize(translate_, playerPosition, false);
    //連番
    bulletCount_++;

    // 挿入
    bullets_.push_back(std::move(bullet));
    break;

  case BulletType::GunBullet:
    // 弾1
    tag = VAR_NAME(GunNormalEnemyBullet);
    bullet = objectManager_->CreateObject<GunNormalEnemyBullet>(
        tag, std::make_shared<GunNormalEnemyBullet>());

    bullet.lock()->Initialize(translate_, playerPosition, false);
    // 連番
    bulletCount_++;

    // 挿入
    bullets_.push_back(std::move(bullet));

    break;
  
  case BulletType::StalkerBullet:
    // 弾1
    tag = VAR_NAME(StalkerEnemyBullet);
    bullet = objectManager_->CreateObject<StalkerEnemyBullet>(
        tag, std::make_shared<StalkerEnemyBullet>());
    bullet.lock()->Initialize(translate_, playerPosition, false);
    // 連番
    bulletCount_++;

  
    // 挿入
    bullets_.push_back(std::move(bullet));

      break;

  case BulletType::DonutBullet:
      // 弾4

      tag = VAR_NAME(DonutNormalEnemyBullet);
      bullet = objectManager_->CreateObject<DonutNormalEnemyBullet>(
          tag, std::make_shared<DonutNormalEnemyBullet>());
      bullet.lock()->Initialize(translate_, playerPosition, false);
      // 連番
      bulletCount_++;

      // 挿入
      //mgrObjList_->push_back(bullet);
      bullets_.push_back(std::move(bullet));

      break;
    }
  



}
