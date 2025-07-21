#pragma once

/**
 * @file BaseNormalEnemyBullet.h
 * @brief 雑魚敵の弾の基底クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"

/// <summary>
/// 弾のタイプ
/// </summary>
enum BulletType {
  CannonBullet,
  GunBullet,
  StalkerBullet,
  DonutBullet,
};


/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager;

/// <summary>
/// 雑魚敵の弾
/// </summary>
class BaseNormalEnemyBullet : public CLEYERA::Component::ObjectComponent {
public:

	/// <summary>
	/// 初期化(引数が無い版)
	/// </summary>
	void Init() override {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="enemyPosition"></param>
	/// <param name="playerPosition"></param>
	/// <param name="isPersistentlyTrack"></param>
	virtual void Initialize(const Math::Vector::Vec3 &enemyPosition,
                          const Math::Vector::Vec3 &playerPosition,const bool &isPersistentlyTrack) = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BaseNormalEnemyBullet()=default;

public:
	/// <summary>
	/// プレイヤー管理クラス
	/// </summary>
	/// <param name="playerManager"></param>
	inline void SetPlayerManager(PlayerManager * playerManager) {
		this->playerManager_ = playerManager;
	}

    /// <summary>
    /// 消去されたかどうか
    /// </summary>
    /// <returns></returns>
    inline bool GetIsDelete() const { return isDelete_; }

protected:
	//プレイヤー管理クラス
	PlayerManager * playerManager_ = nullptr;
	Math::Vector::Vec3 playerPosition_ = {};
	// 雑魚敵本体の座標
    Math::Vector::Vec3 normalEnemyPosition_ = {};
	//永続的にプレイヤーに追跡するかどうか
    bool isPersistentlyTrack_ = false;
    Math::Vector::Vec3 persistentlyPlayerPosition_ = {};
	// 消去されたか
    bool isDelete_ = false;
};