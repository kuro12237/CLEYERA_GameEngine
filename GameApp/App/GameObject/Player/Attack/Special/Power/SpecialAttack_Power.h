#pragma once

#include "SpecialAttack_PowerBullet.h"
#include "../../Interface/IMagicAttack.h"
#include <CLEYERA.h>
#include <limits>


class BaseEnemy;


/* SpecialAttack_Power */
class SpecialAttack_Power : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpecialAttack_Power() = default;
	SpecialAttack_Power(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr, std::weak_ptr<EnemyManager> eneManaPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpecialAttack_Power() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// リセット
	/// </summary>
	void Reset() override;

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void IsAttack() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrwaImGui() override;

private:

	inline float DegreesToRadians(float degrees) {
		return degrees * (3.14159265f / 180.0f);
	}

	void FindNearestEnemy(const Math::Vector::Vec3 & fromPos);

private:

	// 一番近いエネミー
	std::weak_ptr<BaseEnemy> nearestEnemy_;

};
