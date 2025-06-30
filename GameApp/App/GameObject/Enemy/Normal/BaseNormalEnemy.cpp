#include "BaseNormalEnemy.h"

#include "Normal1/NormalEnemy1Bullet.h"
#include "Normal2/NormalEnemy2Bullet.h"

void BaseNormalEnemy::GenerateBullet(const uint32_t &selection) {
  std::shared_ptr<BaseNormalEnemyBullet> bullet = nullptr;

  std::string tag = "";

  switch (selection) {
  case NormalBullet1:
    // 弾1
    bullet = std::make_shared<NormalEnemy1Bullet>();
    bullet->Initialize(translate_, playerPosition_);

    // 名前設定
    tag = this->GetName() + "_" + VAR_NAME(NormalEnemy1Bullet);
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
    bullet = std::make_shared<NormalEnemy2Bullet>();
    bullet->Initialize(translate_, playerPosition_);

    //名前設定
    tag = this->GetName() + "_" + VAR_NAME(NormalEnemy2Bullet);
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
