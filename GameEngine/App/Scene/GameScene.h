#pragma once

#include "IScene.h"
#include "test/TestObject.h"
#include "test/testCamera.h"
#include"Player/PlayerManager.h"
#include"../Util/SceneLoader.h"

class GameScene : public SceneCompornent {
 public:
   GameScene() {}
   ~GameScene() {};

   void Init() override;

   void Update() override;


 private:

	 std::unique_ptr<SceneLoader> loader_ = nullptr;

	 std::shared_ptr<PlayerManager> playerManager_ = nullptr;
};