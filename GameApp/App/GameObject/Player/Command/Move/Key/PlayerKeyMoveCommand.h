#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerCommand.h"


/* Playerの移動処理 */
class PlayerKeyMoveCommand : public IPlayerCommand {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerKeyMoveCommand(const Math::Vector::Vec2 & input);

	/// <summary>
	/// 実行処理
	/// </summary>
	void Exec(PlayerCore* ptr) override;

	/// <summary>
	/// クローン関数
	/// </summary>
	std::unique_ptr<IPlayerCommand> clone() const override {
		return std::make_unique<PlayerKeyMoveCommand>(*this);
	}

private:

	// 移動方向
	Math::Vector::Vec2 keyInput_{};

};
