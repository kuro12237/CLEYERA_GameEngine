#pragma once

/**
 * @file EnemyManager.h
 * @brief 敵管理クラス
 * @author 茂木翼
 */

#include <list>

#include "Boss/BaseBossEnemy.h"
#include "CLEYERA.h"


/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager;

/// <summary>
/// 敵管理クラス
/// </summary>
class EnemyManager : public CLEYERA::Component::ManagerCompornent {
 public:


	/// <summary>
	/// 初期化
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;


    /// <summary>
    /// 雑魚敵
    /// </summary>
    /// <param name="position"></param>
    void GenarateEnemy(const Math::Vector::Vec3 &position);

    /// <summary>
    /// ボス敵
    /// </summary>
    /// <param name="position"></param>
    void GenarateBossEnemyEnemy(const Math::Vector::Vec3 &position);

private:
    /// <summary>
    /// ImGUiの表示
    /// </summary>
    void DisplayImGui();

public:
    /// <summary>
    /// プレイヤー管理クラスの設定
    /// </summary>
    /// <param name="playerManager"></param>
    inline void SetPlayerManager(PlayerManager *playerManager) { 
		this->playerManager_ = playerManager;
	}

private:
	//プレイヤー管理クラス
    PlayerManager *playerManager_ = nullptr;
	//座標
    Math::Vector::Vec3 playerPosition_ = {};

	//雑魚敵
	//std::list<std::unique_ptr<BaseNormalEnemy>> enemyList_;

	//ボス敵
    std::list<std::unique_ptr<BaseBossEnemy>> bossEnemyList_;

    // 生成の文字列を入れる
    std::stringstream enemyPositionsFromCSV_;


};
