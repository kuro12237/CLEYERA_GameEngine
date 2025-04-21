#pragma once
#include"IPlayerCommand.h"
#include"../PlayerCore.h"

class PlayerMoveCommand :public IPlayerCommand{
 public:
   PlayerMoveCommand() {};
   ~PlayerMoveCommand() {};

   void Exec(const std::list<std::weak_ptr<IPlayer>> &p) override;

 private:
};

