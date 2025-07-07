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
  NormalBullet1,
  NormalBullet2,
  NormalBullet3,
};

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
	/// プレイヤーの座標
	/// </summary>
	/// <param name="enemyPosition"></param>
	virtual void SetPlayerPosition(const Math::Vector::Vec3 & enemyPosition) {
		this->playerPosition_ = enemyPosition;
	}

    /// <summary>
    /// 消去されたかどうか
    /// </summary>
    /// <returns></returns>
    inline bool GetIsDelete() const { return isDelete_; }

protected:
    // 雑魚敵本体の座標
    Math::Vector::Vec3 normalEnemyPosition_ = {};
    // プレイヤー
    Math::Vector::Vec3 playerPosition_ = {};
	//永続的にプレイヤーに追跡するかどうか
    bool isPersistentlyTrack_ = false;
    Math::Vector::Vec3 persistentlyPlayerPosition_ = {};
	// 消去されたか
    bool isDelete_ = false;
};