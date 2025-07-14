#include "BaseNormalEnemy.h"

#include "Cannon/CannonNormalEnemy1Bullet.h"
#include "Gun/GunNormalEnemyBullet.h"
#include "Stalker/StalkerEnemyBullet.h"

void BaseNormalEnemy::GenerateBullet(const uint32_t &selection) {
  std::shared_ptr<BaseNormalEnemyBullet> bullet = nullptr;

  std::string tag = "";

  switch (selection) {
  case NormalBullet1:
    // 弾1
    bullet = std::make_shared<CannonNormalEnemy1Bullet>();
    bullet->Initialize(translate_, playerPosition_,false);

    // 名前設定
    tag = this->GetName() + "_" + VAR_NAME(CannonNormalEnemy1Bullet);
    tag = tag + std::to_string(bulletCount_);
    bullet->SetName(tag);
    //連番
    bulletCount_++;

    // 挿入
    mgrObjList_->push_back(bullet);
    bullets_.push_back(std::move(bullet));
    break;

  case NormalBullet2:
    // 弾2
    bullet = std::make_shared<GunNormalEnemyBullet>();
    bullet->Initialize(translate_, playerPosition_,false);

    //名前設定
    tag = this->GetName() + "_" + VAR_NAME(GunNormalEnemyBullet);
    tag = tag + std::to_string(bulletCount_);
    bullet->SetName(tag);
    // 連番
    bulletCount_++;

    // 挿入
    mgrObjList_->push_back(bullet);
    bullets_.push_back(std::move(bullet));

    break;
  
  case NormalBullet3:
      // 弾3
      bullet = std::make_shared<StalkerEnemyBullet>();
      bullet->Initialize(translate_, playerPosition_, false);

      //名前設定
      tag = this->GetName() + "_" + VAR_NAME(StalkerEnemyBullet);
      tag = tag + std::to_string(bulletCount_);
      bullet->SetName(tag);
      // 連番
      bulletCount_++;

      // 挿入
      mgrObjList_->push_back(bullet);
      bullets_.push_back(std::move(bullet));

      break;
    }
}
