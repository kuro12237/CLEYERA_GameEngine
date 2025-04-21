#include "FirstBossEnemy.h"

void FirstBossEnemy::Init() {
   // 名前の設定
   name_ = VAR_NAME(FirstBossEnemy);

   // モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Sphere","Sphere");
   gameObject_->ChangeModel(modelHandle);

   // コライダー作成
   CreateCollider(ColliderType::OBB);

   scale_ = {3.0f, 3.0f, 3.0f};
   // 座標の設定
   translate_ = {.x = 5.0f, .y = 0.5f, .z = 5.0f};
}

void FirstBossEnemy::Update() {

	// 更新
   TransformUpdate();
}
