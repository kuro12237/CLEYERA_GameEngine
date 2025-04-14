#pragma once

/**
 * @file Enemy.h
 * @brief 敵クラス
 * @author 茂木翼
 */


#include "BaseEnemy.h"

/// <summary>
/// 通常の敵
/// </summary>
class Enemy : public BaseEnemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

private:


};
