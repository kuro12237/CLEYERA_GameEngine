#include "FirstBossEnemy.h"

void FirstBossEnemy::Init() {
   // 名前の設定
   name_ = VAR_NAME(FirstBossEnemy);

   // モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Sphere","Sphere");
   gameObject_->ChangeModel(modelHandle);

   // コライダー作成
   CreateCollider(ColliderType::OBB);

   //スケールの設定
   scale_ = {.x = 3.0f, .y = 3.0f, .z = 3.0f};
   // 座標の設定
   translate_ = {.x = 5.0f, .y = 0.5f, .z = 5.0f};
}

void FirstBossEnemy::Update() {


	//方向を取得
   const float_t SPEED = 0.005f;
   velocity_ = (playerPosition_ - translate_) * SPEED;

	// 更新
   TransformUpdate();
}
