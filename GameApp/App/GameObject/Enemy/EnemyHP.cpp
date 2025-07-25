#include "EnemyHP.h"

#include <Enemy/BaseEnemy.h>

void EnemyHPGauge::Init(){

    // モデルの設定
    uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/EnemyHP","EnemyHP.obj");
    gameObject_->ChangeModel(modelHandle);

    // スケールの設定
    scale_ = { .x = 1.0f, .y = 1.0f, .z = 1.0f };


    assert(baseEnemy_);
}

void EnemyHPGauge::Update(){


#ifdef _DEBUG
    ImGui::Begin("EnemyHP");
    ImGui::SliderFloat("Scale", &gaugeScale_, 0.0f, 10.0f);
    ImGui::End();
#endif // _DEBUG

    //スケール
    scale_ = { .x = gaugeScale_, .y = gaugeScale_, .z = gaugeScale_ };
    //座標
    //敵の少し上に置きたい
    translate_ = baseEnemy_->GetPosition();
    translate_.y += HEIGHT_;

    // 更新
    TransformUpdate();
}
