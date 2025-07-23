#pragma once


#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* HighAttack FieldBullet */
class HighAttack_FieldBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HighAttack_FieldBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HighAttack_FieldBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;


};
