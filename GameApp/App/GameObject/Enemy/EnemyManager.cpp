#include "EnemyManager.h"

#include "Player/PlayerManager.h"

// 雑魚敵
#include "Normal/Cannon/CannonNormalEnemy.h"
#include "Normal/Gun/GunNormalEnemy.h"
#include "Normal/Stalker/StalkerNormalEnemy.h"

// ボス
#include "Boss/BakugekiSnipe/BakugekiSnipeBossEnemy.h"
#include "Normal/Donut/DonutNormalEnemy.h"

void EnemyManager::Init() {

  name_ = VAR_NAME(EnemyManager);

  // Luaの読み込み
  lua_ = std::make_unique<LuaScript>();
  lua_->LoadScript("Enemy/Normal/1/GeneratePosition",
                   "Enemy1GeneratePositions");
  lua_->LoadScript("Enemy/Normal/2/GeneratePosition",
                   "Enemy2GeneratePositions");
  lua_->SetReloadCallBack([this]() { LoadEnemy2DataFromLua(); });

  // Luaから抽出したデータの設定
  LoadEnemy2DataFromLua();
  // 生成
  uint32_t enemy1Count =
      lua_->GetVariable<uint32_t>("Enemy1GeneratePositions.count");
  uint32_t enemy2Count =
      lua_->GetVariable<uint32_t>("Enemy2GeneratePositions.count");
  enemy1Count;
  enemy2Count;
#ifdef _DEBUG
  enemy1Count = 1u;
  enemy2Count = 1u;
#endif // _DEBUG

    GenerateCannonNormalEnemy({});
  //GenerateGunNormalEnemy({});
  //GenerateStalkerNormalEnemy({.x = 0.0f, .y = 0.0f, .z = 20.0f});

  //GenerateDonutNormalEnemy({.x=0.0f,.y=0.0f,.z=10.0f});


}

void EnemyManager::Update() {

  enemyCount_ = enemyList_.size();

  // プレイヤーの座標を取得
  playerPosition_ = playerManager_->GetPlayerCore().lock()->GetWorldPos();

  for (std::weak_ptr<BaseNormalEnemy> &enemy : enemyList_) {
    auto it = enemy.lock();
    // プレイヤーの座標を設定
    it->SetPlayerPosition(playerPosition_);

    if (it->GetIsDelete()) {
      it->SetMode(CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE);
    }
  }

  for (std::weak_ptr<BaseBossEnemy> &enemy : bossEnemyList_) {
    // プレイヤーの座標を設定
    enemy.lock()->SetPlayerPosition(playerPosition_);
  }
}

void EnemyManager::GenerateCannonNormalEnemy(const Math::Vector::Vec3 &position) {
  // 敵の生成
  std::weak_ptr<CannonNormalEnemy> enemy =
      objectManager_->CreateObject<CannonNormalEnemy>(
          "CannonNormalEnemy", std::make_shared<CannonNormalEnemy>());

  // 座標の設定
  enemy.lock()->SetInitialPosition(position);

  enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateGunNormalEnemy(const Math::Vector::Vec3 &position) {
  // 敵の生成
  std::weak_ptr<GunNormalEnemy> enemy =
      objectManager_->CreateObject<GunNormalEnemy>(
          "GunNormalEnemy", std::make_shared<GunNormalEnemy>());

  // 座標の設定
  enemy.lock()->SetInitialPosition(position);


  enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateStalkerNormalEnemy(const Math::Vector::Vec3 &position) {
  // 敵の生成
  std::weak_ptr<StalkerNormalEnemy> enemy =
      objectManager_->CreateObject<StalkerNormalEnemy>(
          "StalkerNormalEnemy", std::make_shared<StalkerNormalEnemy>());

  // 座標の設定
  enemy.lock()->SetInitialPosition(position);

  enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateDonutNormalEnemy(const Math::Vector::Vec3 & position){
    // 敵の生成
    std::weak_ptr<DonutNormalEnemy> enemy = 
    objectManager_->CreateObject<DonutNormalEnemy>("DonutNormalEnemy", std::make_shared<DonutNormalEnemy>());
    // 座標の設定
    enemy.lock()->SetInitialPosition(position);
  
    // 挿入
    // 各敵にlistptr持たせる
    enemyList_.push_back(std::move(enemy));
}

void EnemyManager::GenerateBossEnemyEnemy(const Math::Vector::Vec3 &position) {
  // 敵の生成
  std::weak_ptr<BakugekiSnipeBossEnemy> enemy =
      objectManager_->CreateObject<BakugekiSnipeBossEnemy>(
          VAR_NAME(BakugekiSnipeBossEnemy),
          std::make_shared<BakugekiSnipeBossEnemy>());

  // 座標の設定
  enemy.lock()->SetInitialPosition(position);
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
    ImGui::InputInt("Normal", &normalEnemyNumber);
    ImGui::InputInt("Boss", &bossEnemyNumber);

    if (ImGui::TreeNode("Player") == true) {
      ImGui::InputFloat3("Position", &playerPosition_.x);
      ImGui::TreePop();
    }

    ImGui::Separator();

    ImGui::TreePop();
  }
}
