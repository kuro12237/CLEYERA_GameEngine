#include "PlayerMoveCommand.h"

void PlayerMoveCommand::Exec(const std::list<std::weak_ptr<IPlayer>> &p) {

   for (auto obj : p) {
      if (auto it = dynamic_cast<PlayerCore *>(obj.lock().get())) {

         it->Rotate();
         it->Move();

      }
   }
}
