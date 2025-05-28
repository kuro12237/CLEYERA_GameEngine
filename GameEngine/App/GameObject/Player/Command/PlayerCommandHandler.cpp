#include "PlayerCommandHandler.h"
#include "../Command/Attack/Basic/PlayerBasicAttackCommand.h"
#include "../Command/Interface/IPlayerCommand.h"
#include "../Command/Move/Key/PlayerKeyMoveCommand.h"
#include "../Command/Move/Pad/PlayerPadMoveCommand.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerCommandHandler::PlayerCommandHandler(std::weak_ptr<PlayerCore> player) {
  // 入力デバイス
  input_ = CLEYERA::Manager::InputManager::GetInstance();

  // プレイヤーのポインタ
  player_ = player;
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerCommandHandler::Init() {
  // 入力タイするコマンドを登録
  // 移動コマンド
  inputCommandMap_["PadMove"] = []() { return std::make_unique<PlayerPadMoveCommand>(); };
  inputCommandMap_["WKeyMove"] = []() {
    return std::make_unique<PlayerKeyMoveCommand>(Math::Vector::Vec2{0.0f, 1.0f});
  };
  inputCommandMap_["AKeyMove"] = []() {
    return std::make_unique<PlayerKeyMoveCommand>(Math::Vector::Vec2{-1.0f, 0.0f});
  };
  inputCommandMap_["SKeyMove"] = []() {
    return std::make_unique<PlayerKeyMoveCommand>(Math::Vector::Vec2{0.0f, -1.0f});
  };
  inputCommandMap_["DKeyMove"] = []() {
    return std::make_unique<PlayerKeyMoveCommand>(Math::Vector::Vec2{1.0f, 0.0f});
  };

  // 攻撃コマンド
  inputCommandMap_["BasicAttack"] = []() { 
      return std::make_unique<PlayerBasicAttackCommand>(); 
  };
}

/// <summary>
/// 入力に基づいてコマンドを積む
/// </summary>
void PlayerCommandHandler::Handle() {
  
  // 入力がアクティブなときに、コマンドを積む
  // 移動コマンド
  if (input_->IsLJoystickActive()) {
    CommandPush("PadMove");
  }
  if (input_->PushKey(DIK_W)) {
    CommandPush("WKeyMove");
  }
  if (input_->PushKey(DIK_A)) {
    CommandPush("AKeyMove");
  }
  if (input_->PushKey(DIK_S)) {
    CommandPush("SKeyMove");
  }
  if (input_->PushKey(DIK_D)) {
    CommandPush("DKeyMove");
  }

  // 攻撃コマンド
  if (input_->PushBottonPressed(XINPUT_GAMEPAD_A)) {
    CommandPush("BasicAttack");  
  }
}

/// <summary>
/// 実行
/// </summary>
void PlayerCommandHandler::Exec() {
  // キュー内の全コマンドを順次実行
  while (!commands_.empty()) {
    auto &command = commands_.front();
    command->Exec(player_);
    commands_.pop();
  }
}

/// <summary>
/// コマンドのプッシュ
/// </summary>
void PlayerCommandHandler::CommandPush(const std::string &key) {
  auto it = inputCommandMap_.find(key.c_str());
  if (it != inputCommandMap_.end()) {
    commands_.push(it->second());
  }
}
