#pragma once

#include "../Util/SceneLoader.h"
#include "IScene.h"

#include "EnvironmentObject/EnvironmentObject.h"
#include "Player/PlayerManager.h"

class GameScene : public SceneCompornent {
 public:
   GameScene() {}
   ~GameScene() {};

   void Init() override;

   void Update() override;

 private:
   std::unique_ptr<SceneLoader> loader_ = nullptr;

   std::vector<std::shared_ptr<EnvironmentObject>> enviromentObjs_;

   std::shared_ptr<PlayerManager> playerManager_ = nullptr;
};