#include "EnemyManager.h"

#include "Player/PlayerManager.h"
#include "NormalEnemy.h"
#include "Boss/First/FirstBossEnemy.h"

void EnemyManager::Init() {

	//生成
	GenarateEnemy();
    GenarateBossEnemyEnemy();
}

void EnemyManager::Update() {
   
	//プレイヤーの座標を取得
	playerPosition_ = playerManager_->GetPlayerCore()->GetWorldPosition();

	for (std::unique_ptr<BaseNormalEnemy> &enemy : enemyList_) {
		//プレイヤーの座標を設定
        enemy->SetPlayerPosition(playerPosition_);
           // 通常の敵の更新
		enemy->Update();
	}

	for (std::unique_ptr<BaseBossEnemy> &enemy : bossEnemyList_) {
           // プレイヤーの座標を設定
           enemy->SetPlayerPosition(playerPosition_);
		//ボスの更新
		enemy->Update();
    }



	#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG
    


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

void EnemyManager::DisplayImGui() { 
	
	ImGui::Begin("敵管理クラス");
   
	if (ImGui::TreeNode("プレイヤー関係") == true) {
           ImGui::InputFloat3("座標", &playerPosition_.x);
		ImGui::TreePop();

    }
	ImGui::End();
}
