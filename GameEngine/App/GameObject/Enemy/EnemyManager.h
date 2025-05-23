#pragma once

/**
 * @file EnemyManager.h
 * @brief 敵管理クラス
 * @author 茂木翼
 */

#include <list>

#include "Normal/BaseNormalEnemy.h"
#include "Boss/BaseBossEnemy.h"
#include "Lua/Script/LuaScript.h"
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
    /// 雑魚敵を生成
    /// </summary>
    /// <param name="position">座標</param>
    void GenerateEnemy1(const Math::Vector::Vec3 &position);

    /// <summary>
    /// 雑魚敵2を生成
    /// </summary>
    /// <param name="position">座標</param>
    void GenerateEnemy2(const Math::Vector::Vec3 &position);

    /// <summary>
    /// ボス敵
    /// </summary>
    /// <param name="position">座標</param>
    void GenerateBossEnemyEnemy(const Math::Vector::Vec3 &position);

private:
    /// <summary>
    /// ImGUiの表示
    /// </summary>
    void DisplayImGui();

    /// <summary>
    /// Luaの読み込み
    /// </summary>
    void LoadEnemy2DataFromLua();

public:
    /// <summary>
    /// プレイヤー管理クラスの設定
    /// </summary>
    /// <param name="playerManager">プレイヤー管理クラス</param>
    inline void SetPlayerManager(PlayerManager *playerManager) { 
		this->playerManager_ = playerManager;
	}

private:
	//プレイヤー管理クラス
    PlayerManager *playerManager_ = nullptr;
	//座標
    Math::Vector::Vec3 playerPosition_ = {};

	//雑魚敵
	std::list<std::shared_ptr<BaseNormalEnemy>> enemyList_;

    // PlayerCoreのLua
    std::unique_ptr<LuaScript> lua_;

	//ボス敵
    std::list<std::shared_ptr<BaseBossEnemy>> bossEnemyList_;

    // 生成の文字列を入れる
    std::stringstream enemyPositionsFromCSV_;


};
