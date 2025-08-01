#pragma once

#include "../../Interface/IPlayerCommand.h"


/* Playerの移動 */
class PlayerPadMoveCommand : public IPlayerCommand {

public:

	/// <summary>
	/// 実行処理
	/// </summary>
	void Exec(PlayerCore * ptr) override;

	/// <summary>
	/// クローン関数
	/// </summary>
	std::unique_ptr<IPlayerCommand> clone() const override {
		return std::make_unique<PlayerPadMoveCommand>(*this);
	}

};