#include "PlayerCommandHandler.h"

void PlayerCommandHandler::Init() {

   // コマンド作成
   commandList_.push_back(std::make_unique<PlayerMoveCommand>());
   commandList_.push_back(std::make_unique<PlayerActionCommand>());
}

void PlayerCommandHandler::Handler() {

   if (input_->IsLJoystickActive()) {

      for (const auto &command : commandList_) {
         if (std::dynamic_pointer_cast<PlayerMoveCommand>(command)) {
            commands_.push(command);
            break;
         }
      }
   }
   if (input_->PushBottonPressed(XINPUT_GAMEPAD_A)) {

      for (const auto &command : commandList_) {
         if (std::dynamic_pointer_cast<PlayerActionCommand>(command)) {
            commands_.push(command);
            break;
         }
      }
   }
}

void PlayerCommandHandler::Exec() {

   while (!commands_.empty()) {
      auto c = commands_.front().lock();
      c->Exec(players_);
      commands_.pop();
   }
}
