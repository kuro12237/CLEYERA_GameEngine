#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* SpecialAttack PowerBullet */
class SpecialAttack_PowerBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpecialAttack_PowerBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpecialAttack_PowerBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

};