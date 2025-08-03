#pragma once

/**
 * @file BaseEnemy.h
 * @brief 敵の基底クラス
 * @author 茂木翼
 */


#include "CLEYERA.h"
#include "Enemy/EnemyParameter.h"
#include <Enemy/EnemyHPGauge.h>
#include "Component/Hp/HealthComponent.h"


// 前方宣言
class PlayerCore;

/// <summary>
/// 敵の基底クラス
/// </summary>
class ABotton : public CLEYERA::Component::ObjectComponent {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ABotton() {};

    /// <summary>
    /// 初期化
    /// </summary>
    void Init() override;

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;


    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ABotton() {};

public:
    inline void SetIsStart(const bool & isStart) {
        this->isStart_ = isStart;
    }

private:
    bool isStart_ = false;

    float_t addValueY_ = 0.0f;

    float_t theta_ = 0.0f;

};
