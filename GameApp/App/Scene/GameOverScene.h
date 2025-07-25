#pragma once

#include "../Util/SceneLoader.h"
#include "IScene.h"

#include "Enemy/EnemyManager.h"
#include "EnvironmentObject/EnvironmentObject.h"
#include "Item/Manager/ItemManager.h"
#include "Player/PlayerManager.h"
#include "Wall/WallManager.h"


#include "UI/TestUI.h"

class GameOverScene : public SceneComponent {
public:
  GameOverScene() {};
  ~GameOverScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;

private:
  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::weak_ptr<EnvironmentObject>> enviromentObjs_;
};