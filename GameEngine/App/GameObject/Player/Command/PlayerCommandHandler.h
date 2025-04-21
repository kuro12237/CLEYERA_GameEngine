#pragma once
#include "PlayerMoveCommand.h"
#include"PlayerActionCommand.h"

class PlayerCommandHandler {
 public:
   PlayerCommandHandler() { input_ = CLEYERA::Manager::InputManager::GetInstance(); };
   ~PlayerCommandHandler() {};

   void Init();

   void Handler();

   void Exec();

   void SetPlayer(const std::weak_ptr<IPlayer> &p) { players_.push_back(p); }

 private:
   std::list<std::weak_ptr<IPlayer>> players_;
   std::queue<std::weak_ptr<IPlayerCommand>> commands_;
   std::list<std::shared_ptr<IPlayerCommand>> commandList_;

   CLEYERA::Manager::InputManager *input_ = nullptr;
};
