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
#include "Enemy/Normal/Normal1/NormalEnemyBullet.h"

/// <summary>
/// 攻撃
/// </summary>
class NormalEnemyAttack : public NormalEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemyAttack();

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseNormalEnemy"></param>
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

    /// <summary>
    /// 弾を生成
    /// </summary>
    void GenerateBullet();

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
    //弾のリスト
    std::list<std::unique_ptr<NormalEnemyBullet>> bullets_;

    bool isAttack_ = true;
    bool isEndAttack_ = false;

    //プレイヤーの座標を一瞬取得
    Math::Vector::Vec3 playerPosition_ = {};
    bool isGetPlayerPosition_ = false;

};

