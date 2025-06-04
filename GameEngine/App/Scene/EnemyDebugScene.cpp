#include "EnemyDebugScene.h"

void EnemyDebugScene::Init() {
  CLEYERA::Manager::GlobalVariables::GetInstance()->LoadFiles("Configs");

  // プレイヤー管理クラスの生成
  playerManager_ = std::make_unique<PlayerManager>();
  managerCompornents_.push_back(playerManager_);

  // 敵管理クラスの生成
  enemyManager_ = std::make_unique<EnemyManager>();
  // プレイヤー管理クラスの設定
  enemyManager_->SetPlayerManager(playerManager_.get());
  // コンポーネントに挿入
  managerCompornents_.push_back(enemyManager_);

  // 初期化
  for (auto &manager : managerCompornents_) {
    manager->Init();
    // マネージャーのGameObjListをSceneにも登録(weak)
    for (auto &obj : manager->GetObjList()) {

      // 無視
      objectList_.push_back(obj->GetGameObject());

      // 重力適用
      gravityManager_->PushData(obj);
      // 地形当たり判定適用
      terrain_->PushData(obj);
    }
  }

  // 地形モデルの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandle);

  // 無視
  InitRaytracing();
}

void EnemyDebugScene::Update([[maybe_unused]] GameManager *g) {

    if (changeScene_) {

    g->ChangeScene(std::make_unique<GameScene>());
      return;
  }


  for (auto &manager : managerCompornents_) {

    manager->Update();
  }
}

void EnemyDebugScene::ImGuiUpdate() {

  if (ImGui::Button("changeScene")) {
    changeScene_ = true;
    return;
  }
}
