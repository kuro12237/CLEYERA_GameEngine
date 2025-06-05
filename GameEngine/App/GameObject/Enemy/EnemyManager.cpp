#include "EnemyManager.h"

#include "Player/PlayerManager.h"

// 雑魚敵
#include "Normal/Normal1/NormalEnemy1.h"
#include "Normal/Normal2/NormalEnemy2.h"

// ボス
#include "Boss/First/FirstBossEnemy.h"

void EnemyManager::Init() {

  name_ = VAR_NAME(EnemyManager);

  // Luaの読み込み
  lua_ = std::make_unique<LuaScript>();
  lua_->LoadScript("Enemy/Normal/1/GeneratePosition", "Enemy1GeneratePositions");
  lua_->LoadScript("Enemy/Normal/2/GeneratePosition", "Enemy2GeneratePositions");
  lua_->SetReloadCallBack([this]() { LoadEnemy2DataFromLua(); });

  // Luaから抽出したデータの設定
  LoadEnemy2DataFromLua();
  // 生成
  uint32_t enemy1Count = lua_->GetVariable<uint32_t>("Enemy1GeneratePositions.count");
  uint32_t enemy2Count = lua_->GetVariable<uint32_t>("Enemy2GeneratePositions.count");

#ifdef _DEBUG
  enemy1Count = 1u;
  enemy2Count = 1u;
#endif // _DEBUG

  //// 雑魚敵1の生成
  // for (uint32_t i = 1u; i <= enemy1Count; ++i) {
  //   std::string varName = "Enemy1GeneratePositions.translate" + std::to_string(i);
  //   Math::Vector::Vec3 pos = lua_->GetVariable<Math::Vector::Vec3>(varName);
  //   GenerateNormalEnemy1(pos);
  // }

  //// 雑魚敵2の生成
  // for (uint32_t i = 1u; i <= enemy2Count; ++i) {
  //   std::string varName = "Enemy2GeneratePositions.translate" + std::to_string(i);
  //   Math::Vector::Vec3 pos = lua_->GetVariable<Math::Vector::Vec3>(varName);
  //   GenerateNormalEnemy2(pos);
  // }

  for (size_t i = 0; i < 8; i++) {
    std::string tag = "NormalEnemy1";

    char name[17];

    if (i == 0) {

      GenerateNormalEnemy1({}, tag);
    } else {
      std::snprintf(name, sizeof(name), "NormalEnemy1.%03zu", i);

      GenerateNormalEnemy1({}, name);
    }

  }

  for (size_t i = 0; i < 8; i++) {
    std::string tag = "NormalEnemy2";

    char name[17];
    if (i == 0) {

      GenerateNormalEnemy2({}, tag);

    } else {
      std::snprintf(name, sizeof(name), "NormalEnemy2.%03zu", i);

      GenerateNormalEnemy2({}, name);
    }

  }

  for (auto obj : enemyList_) {

    objComponents_.push_back(obj);
  }
}

void EnemyManager::Update() {

  enemyCount_ = enemyList_.size();

  // プレイヤーの座標を取得
  playerPosition_ = playerManager_->GetPlayerCore().lock()->GetWorldPos();

  for (std::shared_ptr<BaseNormalEnemy> &enemy : enemyList_) {
    // プレイヤーの座標を設定
    enemy->SetPlayerPosition(playerPosition_);
    // 雑魚敵の更新
    enemy->Update();
  }

  // 雑魚敵の削除
  enemyList_.remove_if(
      [](const std::shared_ptr<BaseNormalEnemy> &enemy) { return enemy->GetIsDelete(); });

  for (std::shared_ptr<BaseBossEnemy> &enemy : bossEnemyList_) {
    // プレイヤーの座標を設定
    enemy->SetPlayerPosition(playerPosition_);
    // ボスの更新
    enemy->Update();
  }
}

void EnemyManager::GenerateNormalEnemy1(const Math::Vector::Vec3 &position, std::string name) {

  // 敵の生成
  std::shared_ptr<NormalEnemy1> enemy = std::make_shared<NormalEnemy1>();
  // 座標の設定
  enemy->SetInitialPosition(position);
  // 初期化
  enemy->Init();

  if (name != "") {
    enemy->SetName(name);
  }

  // 挿入
  objComponents_.push_back(enemy);
  colliderSystem_->PushCollider(enemy);
  enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateNormalEnemy2(const Math::Vector::Vec3 &position, std::string name) {
  // 敵の生成
  std::shared_ptr<NormalEnemy2> enemy = std::make_shared<NormalEnemy2>();
  // 座標の設定
  enemy->SetInitialPosition(position);
  // 初期化
  enemy->Init();

  if (name != "") {
    enemy->SetName(name);
  }

  // 挿入
  objComponents_.push_back(enemy);
  colliderSystem_->PushCollider(enemy);
  enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateBossEnemyEnemy(const Math::Vector::Vec3 &position) {
  // ボスの生成
  std::shared_ptr<BaseBossEnemy> enemy = std::make_shared<FirstBossEnemy>();
  // 初期化
  enemy->Init();
  // 座標の設定
  enemy->SetInitialPosition(position);
  // 挿入
  objComponents_.push_back(enemy);
  colliderSystem_->PushCollider(enemy);
  bossEnemyList_.push_back(std::move(enemy));
}

void EnemyManager::LoadEnemy2DataFromLua() {
  // translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}

void EnemyManager::ImGuiUpdate() {

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    int32_t normalEnemyNumber = static_cast<int32_t>(enemyList_.size());
    int32_t bossEnemyNumber = static_cast<int32_t>(bossEnemyList_.size());
    ImGui::InputInt("雑魚敵", &normalEnemyNumber);
    ImGui::InputInt("ボス敵", &bossEnemyNumber);

    if (ImGui::TreeNode("Player") == true) {
      ImGui::InputFloat3("Position", &playerPosition_.x);
      ImGui::TreePop();
    }

    ImGui::Separator();

    for (auto obj : objComponents_) {

      obj.lock()->ImGuiUpdate();
    }

    ImGui::TreePop();
  }
}
