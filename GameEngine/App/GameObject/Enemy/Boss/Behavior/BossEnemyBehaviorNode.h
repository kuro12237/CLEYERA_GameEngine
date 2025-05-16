#pragma once

/**
 * @file BossEnemyBehaviorNode.h
 * @brief ボスのノードクラス
 * @author 茂木翼
 */

#include <memory>
#include <vector>
#include <string>

#include "Enemy/EnemyNodeState.h"

/// <summary>
/// ボス敵
/// </summary>
class BaseBossEnemy;

/// <summary>
/// ボス用のノード
/// </summary>
class BossEnemyBehaviorNode {
public:

	/// <summary>
	/// 処理
	/// </summary>
	/// <param name="baseBossEnemy"></param>
	/// <returns></returns>
	virtual EnemyNodeState Execute(BaseBossEnemy* baseBossEnemy) = 0;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BossEnemyBehaviorNode() = default;


};
