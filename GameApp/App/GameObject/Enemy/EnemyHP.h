#pragma once

/**
 * @file EnemyHPGauge.h
 * @brief 敵の体力クラス
 * @author 茂木翼
 */


#include "CLEYERA.h"
#include "Enemy/EnemyParameter.h"

/// <summary>
/// 敵
/// </summary>
class BaseEnemy;

/// <summary>
/// 敵の体力ゲージクラス
/// </summary>
class EnemyHPGauge : public CLEYERA::Component::ObjectComponent {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyHPGauge(const int32_t & maxHP,BaseEnemy* baseEnemy) {
        this->maxHP_ = maxHP;
        this->baseEnemy_ = baseEnemy;
    };

    /// <summary>
    /// 初期化
    /// </summary>
    void Init()override;

    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyHPGauge()=default;



private:
    //敵
    BaseEnemy * baseEnemy_ = nullptr;
private:
    //高さ
    const float_t HEIGHT_ = 2.0f;

private:
    
    //最大HP
    int32_t maxHP_ = 0u;

    //ゲージのスケール
    float_t gaugeScale_ = 1.0f;


};
