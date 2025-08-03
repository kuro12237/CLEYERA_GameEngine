#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* LowAttack BackBullet */
class LowAttack_BackBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowAttack_BackBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowAttack_BackBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 衝突時コールバック
	/// </summary>
	void OnCollision(std::weak_ptr<ObjectComponent> other) override;

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

};
