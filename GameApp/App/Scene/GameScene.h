#pragma once

#include "../Util/SceneLoader.h"
#include "IScene.h"

#include "Enemy/EnemyManager.h"
#include "EnvironmentObject/EnvironmentObject.h"
//#include "Item/Manager/ItemManager.h"
#include "Player/PlayerManager.h"
#include "Wall/WallManager.h"

#include "TestPlayGui/TestPlayGui.h"

#include "UI/TestUI.h"

class GameScene : public SceneCompornent {
public:
	GameScene();
  ~GameScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;


private:
  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::shared_ptr<EnvironmentObject>> enviromentObjs_;

  std::shared_ptr<ItemManager> itemManager_;

  std::shared_ptr<PlayerManager> playerManager_;
  // 敵管理クラス
  std::shared_ptr<EnemyManager> enemyManager_ = nullptr;

  std::shared_ptr<WallManager> wallManager_ = nullptr;

  std::shared_ptr<TestPlayGui> imgui_ = nullptr;

  std::vector<std::shared_ptr<TestUI>> uis_;
};