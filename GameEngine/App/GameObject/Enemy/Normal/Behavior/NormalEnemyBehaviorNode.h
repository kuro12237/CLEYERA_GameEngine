#pragma once

/**
 * @file NormalEnemyBehaviorNode.h
 * @brief 雑魚敵のノードクラス
 * @author 茂木翼
 */

#include <memory>
#include <vector>
#include <string>

#include "Enemy/EnemyNodeState.h"


/// <summary>
/// ボス敵
/// </summary>
class BaseNormalEnemy;

/// <summary>
/// 雑魚敵用のノード
/// </summary>
class NormalEnemyBehaviorNode {
public:

	/// <summary>
	/// 処理
	/// </summary>
	/// <param name="baseNormalEnemy">雑魚敵</param>
	/// <returns>ノードの状態</returns>
	virtual EnemyNodeState Execute(BaseNormalEnemy * baseNormalEnemy) = 0;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~NormalEnemyBehaviorNode() = default;


};
