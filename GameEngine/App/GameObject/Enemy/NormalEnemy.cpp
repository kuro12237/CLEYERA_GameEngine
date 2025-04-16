#include "NormalEnemy.h"

void NormalEnemy::Init() {

	//名前の設定
   name_ = VAR_NAME(NormalEnemy);

   //モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
   gameObject_->ChangeModel(modelHandle);


   //コライダー作成
   CreateCollider(ColliderType::OBB);

   //座標の設定
   translate_ = {.x = 0.0f, .y = 0.0f, .z = 5.0f};

}

void NormalEnemy::Update() {



	//更新
	TransformUpdate();
}
