#pragma once
#include "../Util/SceneLoader.h"
#include "IScene.h"
#include"../GameManager/GameManager.h"


#include "Enemy/EnemyManager.h"
#include "EnvironmentObject/EnvironmentObject.h"
#include "Item/Manager/ItemManager.h"
#include "Player/PlayerManager.h"
#include "Wall/WallManager.h"


#include "UI/TestUI.h"

class GameClearScene : public SceneComponent {
public:
  GameClearScene() {};
  ~GameClearScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;

private:
  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::weak_ptr<EnvironmentObject>> enviromentObjs_;
};