#include "PlayerCommandHandler.h"
#include "../Command/Attack/Basic/PlayerBasicAttackCommand.h"
#include "../Command/Attack/Signature/PlayerSignatureAttackCommand.h"
#include "../Command/Attack/Standard/PlayerStandardAttackCommand.h"
#include "../Command/Interface/IPlayerCommand.h"
#include "../Command/Move/Key/PlayerKeyMoveCommand.h"
#include "../Command/Move/Pad/PlayerPadMoveCommand.h"
#include "../Command/Dash/PlayerDashCommand.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerCommandHandler::PlayerCommandHandler(PlayerCore * ptr) {
  // 入力デバイス
  input_ = CLEYERA::Manager::InputManager::GetInstance();

  // プレイヤーのポインタ
  p_Player_ = ptr;
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
  inputCommandMap_["BasicAttack"] = []() { return std::make_unique<PlayerBasicAttackCommand>(); };
  inputCommandMap_["SignatureAttack"] = []() { return std::make_unique<PlayerSignatureAttackCommand>(); };
  inputCommandMap_["StandardAttack"] = []() { return std::make_unique<PlayerStandardAttackCommand>(); };

  // ダッシュコマンド
  inputCommandMap_["Dash" ] = []() { return std::make_unique<PlayerDashCommand>(); };

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
  if (input_->PushBottonPressed(XINPUT_GAMEPAD_X)) {
    CommandPush("BasicAttack");
  }
  if (input_->PushBottonPressed(XINPUT_GAMEPAD_Y)) {
    CommandPush("StandardAttack");
  }
  if (input_->PushBottonPressed(XINPUT_GAMEPAD_B)) {
    CommandPush("SignatureAttack");
  }

  // ダッシュコマンド
  if ( input_->PushBottonPressed(XINPUT_GAMEPAD_A) ) {
      CommandPush("Dash");
  }
}

/// <summary>
/// 実行
/// </summary>
void PlayerCommandHandler::Exec() {
  // キュー内の全コマンドを順次実行
  while (!commands_.empty()) {
    auto &command = commands_.front();
    command->Exec(p_Player_);
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
