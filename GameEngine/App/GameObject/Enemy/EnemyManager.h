#pragma once

/**
 * @file EnemyManager.h
 * @brief 敵管理クラス
 * @author 茂木翼
 */

#include <list>

#include "NormalEnemy.h"
#include "Boss/BaseBossEnemy.h"



/// <summary>
/// 敵管理クラス
/// </summary>
class EnemyManager {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


	/// <summary>
	/// 雑魚敵
	/// </summary>
	void GenarateEnemy();

	/// <summary>
	/// ボス敵
	/// </summary>
    void GenarateBossEnemyEnemy();

private:
	//雑魚敵
	std::list<std::unique_ptr<IEnemy>> enemyList_;

	//ボス敵
    std::list<std::unique_ptr<BaseBossEnemy>> bossEnemyList_;



};
