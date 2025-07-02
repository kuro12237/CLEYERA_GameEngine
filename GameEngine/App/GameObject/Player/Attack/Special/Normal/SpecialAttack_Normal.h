#pragma once

#include "SpecialAttack_NormalBullet.h"
#include "../../Interface/IMagicAttack.h"
#include <CLEYERA.h>


/* SpecialAttack_Normal */
class SpecialAttack_Normal : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpecialAttack_Normal() = default;
	SpecialAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpecialAttack_Normal() = default;

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

	/// <summary>
	/// 指定した軸の周りにベクトルを回転させます。
	/// </summary>
	Math::Vector::Vec3 RotateAroundAxis(const Math::Vector::Vec3 & v, const Math::Vector::Vec3 & axis,
										float angle);

	/// <summary>
	/// バレットの名前の生成
	/// </summary>
	std::string GenerateBulletName(const std::string & baseTag, size_t count);

private:

	// スクリプト
	std::unique_ptr<LuaScript> lua_;

	// 弾の出る方向
	int directionCount_ = 0;
};
