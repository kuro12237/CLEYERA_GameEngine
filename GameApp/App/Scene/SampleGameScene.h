#pragma once

#include "../GameManager/GameManager.h"
#include "../Util/SceneLoader.h"
#include "IScene.h"

#include "../SampleObj/Coin.h"
#include "curl/curl.h"

#include"../SampleObj/ScoreFunc.h"

class SampleGameScene : public SceneComponent {
public:
  SampleGameScene() {};
  ~SampleGameScene() {};

  void Init() override;

  void Update(GameManager *g) override;

  void Draw2d() override;

private:
  std::vector<std::shared_ptr<Coin>> coins_;

  bool isSelect_ = false;
  bool isEnemyAttack_ = false;
  bool isReset_ = false;

  std::random_device rd;
  int scores_ = 0;
  bool gameReset_ = false;

  std::future<std::string> getScoreFuture_;
  std::string rankText_ = "読み込み中...";


};