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


private:

	/// <summary>
	/// ウェーブ
	/// </summary>
	void Wave();


private:

	float frameCount_ = 0.0f;
	float expandDuration_ = 18.0f;
	float shrinkDuration_ = 18.0f;
	float maxScale_ = 5.0f;

	enum Phase { Expand, Shrink } phase_ = Expand;

};
