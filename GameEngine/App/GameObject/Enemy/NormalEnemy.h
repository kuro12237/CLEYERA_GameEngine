#pragma once

/**
 * @file NormalEnemy.h
 * @brief 通常の敵クラス
 * @author 茂木翼
 */


#include "IEnemy.h"

/// <summary>
/// 通常の敵
/// </summary>
class NormalEnemy : public IEnemy {
public:
	/// <summary>
	/// 通常の敵
	/// </summary>
	NormalEnemy()=default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemy() override=default;

private:


};
