#pragma once
#include "pch/Pch.h"

class IPlayer;
class IPlayerCommand {
 public:
   IPlayerCommand() {};
   virtual ~IPlayerCommand() {};

   virtual void Exec(const std::list<std::weak_ptr<IPlayer>> &p) = 0;

 private:
};
