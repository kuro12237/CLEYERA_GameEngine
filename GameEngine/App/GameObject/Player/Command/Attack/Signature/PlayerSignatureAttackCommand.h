#pragma once

#include "../../Interface/IPlayerCommand.h"

/* Playerのベーシック攻撃 */
class PlayerSignatureAttackCommand : public IPlayerCommand {

public:
  /// <summary>
  /// 実行処理
  /// </summary>
  void Exec(const std::weak_ptr<PlayerCore> &player) override;

  /// <summary>
  /// クローン関数
  /// </summary>
  std::unique_ptr<IPlayerCommand> clone() const override {
    return std::make_unique<PlayerSignatureAttackCommand>(*this);
  }
};
