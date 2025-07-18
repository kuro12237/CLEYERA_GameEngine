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

#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"


class DebugSelectScene : public SceneComponent {
public:
  DebugSelectScene() {};
  ~DebugSelectScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;

private:

  std::vector<std::string> sceneNames_;
  int selectedIndex_ = 0;

  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::shared_ptr<EnvironmentObject>> enviromentObjs_;



  bool f_ = false;
};