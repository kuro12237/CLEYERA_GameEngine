#pragma once

#include "HighAttack_NormalBullet.h"
#include "../../Interface/IMagicAttack.h"
#include <CLEYERA.h>


/* HighAttack Normal */
class HighAttack_Normal : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HighAttack_Normal() = default;
	HighAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HighAttack_Normal() = default;

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
	/// 攻撃開始
	/// </summary>
	void StartAttack(); 

	/// <summary>
	///  1発発射
	/// </summary>
	void FireOneBullet(int columnIndex);

	/// <summary>
	/// バレットの名前の生成
	/// </summary>
	std::string GenerateBulletName(const std::string & baseTag, size_t count);


private:

	// スクリプト
	std::unique_ptr<LuaScript> lua_;

	// 連射用制御
	int shotIndex_ = 0;         // 発射した弾のインデックス(0〜5)
	int shotsPerSequence_ = 0;  // 合計発射数
	int shotsPerRow_ = 0;       // 1列あたりの弾数（右・中・左）
	float shotInterval_ = 0.0f; // 発射間隔（フレーム数）
	float shotTimer_ = 0.0f;    // 発射タイマー

	bool isShooting_ = false; // 攻撃開始フラグ
};


