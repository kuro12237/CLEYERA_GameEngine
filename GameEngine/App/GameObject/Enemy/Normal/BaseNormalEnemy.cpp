#include "BaseNormalEnemy.h"

#include "Normal1/NormalEnemy1Bullet.h"
#include "Normal2/NormalEnemy2Bullet.h"

void BaseNormalEnemy::GenerateBullet(const uint32_t &selection) {
  std::shared_ptr<BaseNormalEnemyBullet> bullet = nullptr;

	switch ( selection ) { 
	case NormalBulletType::NormalBullet1:
          // 弾1
          bullet = std::make_shared<NormalEnemy1Bullet>();
          bullet->Initialize(translate_,playerPosition_);

          colliderSystem_->PushCollider(bullet);
          // 挿入
          bullets_.push_back(std::move(bullet));

		break;

	case NormalBulletType::NormalBullet2:
          // 弾2
          bullet = std::make_shared<NormalEnemy2Bullet>();
          bullet->Initialize(translate_, playerPosition_);

          colliderSystem_->PushCollider(bullet);
          // 挿入
          bullets_.push_back(std::move(bullet));

        break;
	}
}
