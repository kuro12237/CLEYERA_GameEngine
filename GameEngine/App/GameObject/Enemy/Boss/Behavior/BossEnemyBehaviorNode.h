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

public:
	/// <summary>
	/// ノードの名前を取得
	/// </summary>
	/// <returns></returns>
	virtual std::string GetNodeName() const { 
		return nodeName_;
	}

protected:
	//ノードの名前
	std::string nodeName_ = "";

};
