#pragma once

/**
 * @file BossEnemyAttack.h
 * @brief 攻撃ノードクラス
 * @author 茂木翼
 */


 //Actionノードについて
 //このクラスのように実行するだけのクラス
 //つまり具体的な動きをここで行う
 //子を持つことができない

#include <list>

#include "Enemy/Boss/Behavior/BossEnemyBehaviorNode.h"
#include "Enemy/Normal/Normal1/NormalEnemy1Bullet.h"
#include "Enemy/Normal/Normal2/NormalEnemy2Bullet.h"

/// <summary>
/// 攻撃
/// </summary>
class BossEnemyAttack : public BossEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="bulletType">弾の種類</param>
    BossEnemyAttack(const uint32_t &bulletType) { this->bulletType_ = bulletType; };

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy"雑魚敵></param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseBossEnemy * baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemyAttack() = default;

private:
    //時間変化
    const float_t DELTA_TIME_ = 1.0f / 60.0f;
    //クールタイムの長さ
    const float_t COOL_TIME_LENGTH_ = 2.0f;
    //攻撃の長さ
    const float_t ATTACK_TIME_LENGTH_ = 3.0f;

    //弾の最大の高さ
    const float_t BULLET_MAX_HEIGHT_ = 1.0f;

private:
    //弾の種類
    uint32_t bulletType_ = 0u;

    //攻撃準備
    bool isReadyForAttack_ = true;
    bool isAttackFinished_ = false;

    //プレイヤーの座標を一瞬取得
    Math::Vector::Vec3 playerPosition_ = {};
    bool isGetPlayerPosition_ = false;

    //生成時間
    float_t generateTime_ = 0.0f;

    bool hasAttacked_ = false;
};

