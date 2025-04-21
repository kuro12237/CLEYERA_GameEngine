#include "EnemyManager.h"

#include "NormalEnemy.h"
#include "Boss/First/FirstBossEnemy.h"

void EnemyManager::Init() {

	//生成
	GenarateEnemy();
        GenarateBossEnemyEnemy();
}

void EnemyManager::Update() {
   
	for (std::unique_ptr<BaseNormalEnemy> &enemy : enemyList_) {
		//通常の敵の更新
		enemy->Update();
	}

	for (std::unique_ptr<BaseBossEnemy> &enemy : bossEnemyList_) {
		//ボスの更新
		enemy->Update();
    }


}

void EnemyManager::GenarateEnemy() {

	// 敵の生成
   std::unique_ptr<BaseNormalEnemy> enemy = std::make_unique<NormalEnemy>();
   // 初期化
   enemy->Init();
   // 挿入
   enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenarateBossEnemyEnemy() {
   // ボスの生成
   std::unique_ptr<BaseBossEnemy> enemy = std::make_unique<FirstBossEnemy>();
   // 初期化
   enemy->Init();
   // 挿入
   bossEnemyList_.push_back(std::move(enemy));
}
