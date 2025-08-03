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

class TitleScene : public SceneComponent {
public:
  TitleScene() {};
  ~TitleScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;


  inline bool GetIsStart()const {
	  return isStart_;
  }

  void SetIsEndProcess(const bool & isEndProcess) {
	  this->isEndProcess_ = isEndProcess;
  }

private:
  std::unique_ptr<SceneLoader> loader_ = nullptr;

  std::vector<std::weak_ptr<EnvironmentObject>> enviromentObjs_;

  bool isStart_ = false;

  bool isEndProcess_ = false;


};