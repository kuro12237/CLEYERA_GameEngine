#pragma once

#include "../../Interface/IPlayerCommand.h"


/* Playerの移動処理 */
class PlayerPadMoveCommand : public IPlayerCommand {

public:

	/// <summary>
	/// 実行処理
	/// </summary>
	void Exec(const std::weak_ptr<PlayerCore> & player) override;

	/// <summary>
	/// クローン関数
	/// </summary>
	std::unique_ptr<IPlayerCommand> clone() const override {
		return std::make_unique<PlayerPadMoveCommand>(*this);
	}

};