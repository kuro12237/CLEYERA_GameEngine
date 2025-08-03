#pragma once

#include "../../Interface/IMagicAttack.h"
#include "HighAttack_FieldBullet.h"
#include <CLEYERA.h>


/* HighAttack Field */
class HighAttack_Field : public IMagicAttack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HighAttack_Field() = default;
	HighAttack_Field(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr, std::weak_ptr<EnemyManager> eneManaPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HighAttack_Field() = default;

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

};

