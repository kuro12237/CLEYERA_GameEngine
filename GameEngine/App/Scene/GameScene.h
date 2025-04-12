#pragma once

#include "IScene.h"
#include "test/TestObject.h"
#include "test/testCamera.h"
#include"Player/PlayerManager.h"

class GameScene : public SceneCompornent {
 public:
   GameScene() {}
   ~GameScene() {};

   void Init() override;

   void Update() override;

   void ImGuiUpdate() override;

 private:
};