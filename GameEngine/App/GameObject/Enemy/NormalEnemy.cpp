#include "NormalEnemy.h"

void NormalEnemy::Init() {

	//名前の設定
   name_ = VAR_NAME(NormalEnemy);

   //モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
   gameObject_->ChangeModel(modelHandle);


   //コライダー作成
   CreateCollider(ColliderType::OBB);

   

}

void NormalEnemy::Update() {
   // 方向を取得
   const float_t SPEED = 0.005f;
   velocity_ = (playerPosition_ - translate_) * SPEED;




	//更新
	TransformUpdate();
}
