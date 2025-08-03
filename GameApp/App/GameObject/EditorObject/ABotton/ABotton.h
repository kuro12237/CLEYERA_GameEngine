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
class TitleScene;

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
    void SetTitleScene(TitleScene * titleScene);

    inline void SetIsStart(const bool & isStart) {
        this->isStart_ = isStart;
    }

    const float_t DELTA_TIME_ = 1.0f / 60.0f;

private:

    TitleScene * titleScene_ = nullptr;

    bool isStart_ = false;

    float_t addValueY_ = 0.0f;
    float_t tmpY_ = 0.0f;

    float_t theta2_ = 0.0f;
    float_t t_ = 0.0f;
    float_t theta_ = 0.0f;

    bool isEndProcess_ = false;

    float_t timer_ = 0.0f;

};
