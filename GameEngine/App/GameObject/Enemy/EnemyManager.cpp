#include "EnemyManager.h"

#include "Player/PlayerManager.h"
#include "Boss/First/FirstBossEnemy.h"
#include "Normal/Normal1/NormalEnemy1.h"

void EnemyManager::Init() {

   std::ifstream file;
   file.open("Resources/Configs/Entitiys/Enemy/EnemyInitialPosition.csv");
   // 開かなかったら止まる
   assert(file.is_open());

   // ファイルの内容を文字列ストリームにコピー
   enemyPositionsFromCSV_ << file.rdbuf();
   // ファイルを閉じる
   file.close();

   // 1行分の文字列を入れる変数
   std::string line;

   // コマンド実行ループ
   while (std::getline(enemyPositionsFromCSV_, line)) {

      // 1行分の文字列をストリームに変換して解析しやすくする
      std::istringstream lineStream(line);

      std::string word;
      //,区切りで行の先頭文字列を取得
      std::getline(lineStream, word, ',');

      // 「//」があった行の場合コメントなので飛ばす
      if (word.find("//") == 0) {
         // コメントは飛ばす
         continue;
      }

      // 通常の敵の場合
      if (word.find("NormalEnemy") == 0) {
         Math::Vector::Vec3 position = {};
         // X座標
         std::getline(lineStream, word, ',');
         position.x = static_cast<float>(std::atof(word.c_str()));

         // Y座標
         std::getline(lineStream, word, ',');
         position.y = static_cast<float>(std::atof(word.c_str()));

         // Z座標
         std::getline(lineStream, word, ',');
         position.z = static_cast<float>(std::atof(word.c_str()));

         position.y = 0.5f;
         // 生成
         GenarateEnemy(position);

      }
      // 強敵の場合
      else if (word.find("StrongEnemy") == 0) {
         Math::Vector::Vec3 position = {};
         // X座標
         std::getline(lineStream, word, ',');
         position.x = static_cast<float>(std::atof(word.c_str()));

         // Y座標
         std::getline(lineStream, word, ',');
         position.y = static_cast<float>(std::atof(word.c_str()));

         // Z座標
         std::getline(lineStream, word, ',');
         position.z = static_cast<float>(std::atof(word.c_str()));
         position.y = 0.5f;
         // 生成
         //GenarateBossEnemyEnemy(position);
      }
   }

   

}

void EnemyManager::Update() {
   
	//プレイヤーの座標を取得
    playerPosition_ = playerManager_->GetPlayerCore().lock()->GetWorldPos();

	for (std::shared_ptr<BaseNormalEnemy> &enemy : enemyList_) {
		//プレイヤーの座標を設定
        enemy->SetPlayerPosition(playerPosition_);
           // 通常の敵の更新
		enemy->Update();
	}

	for (std::shared_ptr<BaseBossEnemy> &enemy : bossEnemyList_) {
           // プレイヤーの座標を設定
           enemy->SetPlayerPosition(playerPosition_);
		//ボスの更新
		enemy->Update();
    }



	#ifdef _DEBUG
    DisplayImGui();
#endif // _DEBUG
    


}

void EnemyManager::GenarateEnemy(const Math::Vector::Vec3 &position) {

	//// 敵の生成
  std::shared_ptr<NormalEnemy1> enemy = std::make_shared<NormalEnemy1>();
    //座標の設定
    enemy->SetInitialPosition(position);
    // 初期化
    enemy->Init();
    //挿入
    enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenarateBossEnemyEnemy(const Math::Vector::Vec3 &position) {
   // ボスの生成
  std::shared_ptr<BaseBossEnemy> enemy = std::make_shared<FirstBossEnemy>();
   // 初期化
   enemy->Init();
   // 座標の設定
   enemy->SetInitialPosition(position);
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
