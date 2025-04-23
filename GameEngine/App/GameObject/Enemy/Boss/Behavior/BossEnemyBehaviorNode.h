#pragma once


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
/// ボス用のノード
/// </summary>
class BossEnemyBehaviorNode {
public:

	/// <summary>
	/// 処理
	/// </summary>
	virtual NodeState Tick() = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BossEnemyBehaviorNode() = default;

};
