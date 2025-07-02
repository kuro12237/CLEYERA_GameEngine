#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* LowAttack NormalBullet */
class LowAttack_NormalBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowAttack_NormalBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowAttack_NormalBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

#pragma region Accessor

	// コンボステップ
	void SetComboStep(uint32_t step) { comboStep_ = step; }

#pragma endregion

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

private:

	// コンボステップ
	uint32_t comboStep_ = 0;

};
