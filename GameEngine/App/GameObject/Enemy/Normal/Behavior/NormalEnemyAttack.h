#pragma once

/**
 * @file NormalEnemyAttack.h
 * @brief 攻撃ノードクラス
 * @author 茂木翼
 */


 //Actionノードについて
 //このクラスのように実行するだけのクラス
 //つまり具体的な動きをここで行う
 //子を持つことができない

#include <list>

#include "NormalEnemyCondition.h"
#include "Enemy/Normal/Normal1/NormalEnemy1Bullet.h"
#include "Enemy/Normal/Normal2/NormalEnemy2Bullet.h"

/// <summary>
/// 攻撃
/// </summary>
class NormalEnemyAttack : public NormalEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="bulletType">弾の種類</param>
    NormalEnemyAttack(const uint32_t&bulletType);

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy"雑魚敵></param>
    /// <returns></returns>
    EnemyNodeState Execute(BaseNormalEnemy * baseNormalEnemy) override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemyAttack() = default;

private:
    /// <summary>
    /// ImGuiの表示
    /// </summary>
    void DisplayImGui();

    
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

};

