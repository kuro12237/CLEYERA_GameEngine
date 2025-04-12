#pragma once
#include"../Scene/IScene.h"
#include"../Scene/DebugScene.h"
#include"../Scene/GameScene.h"

class GameManager {
 public:
   GameManager();
   ~GameManager() {};

   void Run();

 private:
   std::unique_ptr<Engine> engine_ = nullptr;

   std::unique_ptr<SceneCompornent> scene_ = nullptr;
};
