#include "App/GameManager/GameManager.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

   std::unique_ptr<GameManager> game = std::make_unique<GameManager>();
   game->Run();
}