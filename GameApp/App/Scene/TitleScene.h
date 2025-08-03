#pragma once
#include "../GameManager/GameManager.h"
#include "../Util/SceneLoader.h"
#include "IScene.h"

#include "Enemy/EnemyManager.h"
#include "EnvironmentObject/EnvironmentObject.h"
#include "Item/Manager/ItemManager.h"
#include "Player/PlayerManager.h"
#include "Wall/WallManager.h"

#include "../Util/SceneChangeAnim.h"
#include "UI/TestUI.h"

class TitleScene : public SceneComponent {
public:
  TitleScene() {};
  ~TitleScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;

private:
  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::weak_ptr<EnvironmentObject>> enviromentObjs_;

  std::unique_ptr<SceneChangeAnim> sceneAnim_ = nullptr;
};