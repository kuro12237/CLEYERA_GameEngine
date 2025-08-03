#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerBullet.h"

/* SpecialAttack NormalBullet */
class SpecialAttack_NormalBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpecialAttack_NormalBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpecialAttack_NormalBullet() = default;

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
