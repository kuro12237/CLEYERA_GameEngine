#pragma once
#include "../PlayerCore.h"
#include "IPlayerCommand.h"
#include"../Bullet/PlayerBulletManager.h"

class PlayerActionCommand : public IPlayerCommand {
 public:
   PlayerActionCommand() {};
   ~PlayerActionCommand() {};

   void Exec(const std::list<std::weak_ptr<IPlayer>> &p) override;

 private:
};