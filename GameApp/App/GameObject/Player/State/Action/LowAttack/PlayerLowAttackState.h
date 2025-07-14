#pragma once

#include "../Interface/IPlayerActionState.h"


class PlayerLowAttackState : public IPlayerActionState {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerLowAttackState() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLowAttackState() = default;

	/// <summary>
	/// 純粋仮想関数
	/// </summary>
	void Enter(PlayerCore * ptr) override;
	void Update() override;
	void HandleInput() override;
	void Exit() override;

private:

};