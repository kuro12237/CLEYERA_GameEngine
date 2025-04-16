#include "EnemyManager.h"

#include "NormalEnemy.h"
#include "Boss/First/FirstBossEnemy.h"

void EnemyManager::Initialize() {




}

void EnemyManager::Update() {



}

void EnemyManager::GenarateEnemy() {

	// 敵の生成
   std::unique_ptr<IEnemy> enemy = std::make_unique<NormalEnemy>();
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
