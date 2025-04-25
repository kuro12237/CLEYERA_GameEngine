#pragma once

/**
 * @file BossEnemyBehaviorNode.h
 * @brief ボスのノードクラス
 * @author 茂木翼
 */

#include <memory>
#include <vector>
#include <string>

/// <summary>
/// ノードの状態
/// </summary>
enum NodeState {
	//成功
	Success,
	//失敗
	Failure,
	//実行
	Running,
};

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
	virtual NodeState Execute(BaseBossEnemy* baseBossEnemy) = 0;

	
	/// <summary>
	/// 状態の名前を取得
	/// </summary>
	/// <returns></returns>
	inline virtual std::string GetConditionName()const{
		return conditionName_;
	}
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BossEnemyBehaviorNode() = default;


protected:
	//状態の名前
	std::string conditionName_ = "";

};
