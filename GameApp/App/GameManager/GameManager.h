#pragma once
#include"../Scene/IScene.h"
#include"../Scene/GameScene.h"

#include"CLEYERA.h"
#pragma comment(lib, "Engine.lib")


class GameManager {
 public:
   GameManager();
   ~GameManager() {};

   void Run();

   /// <summary>
   /// Scene切替
   /// </summary>
   /// <param name="newScene"></param>
   void ChangeScene(std::unique_ptr<SceneCompornent> newScene);

 private:
   std::unique_ptr<Engine> engine_ = nullptr;

   std::unique_ptr<SceneCompornent> scene_ = nullptr;

   bool isChange_ = false;
};
