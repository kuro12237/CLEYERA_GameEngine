#include "BaseNormalEnemy.h"

#include "Normal1/NormalEnemy1Bullet.h"
#include "Normal2/NormalEnemy2Bullet.h"

void BaseNormalEnemy::GenerateBullet(const uint32_t &selection) {
  std::unique_ptr<BaseNormalEnemyBullet> bullet = nullptr;

	switch ( selection ) { 
	case NormalBullet1:
          // 弾1
          bullet = std::make_unique<NormalEnemy1Bullet>();
          bullet->Initialize(translate_,playerPosition_);
          // 挿入
          bullets_.push_back(std::move(bullet));

		break;

	case NormalBullet2:
          // 弾2
          bullet = std::make_unique<NormalEnemy2Bullet>();
          bullet->Initialize(translate_, playerPosition_);
          // 挿入
          bullets_.push_back(std::move(bullet));

        break;
	}
}
