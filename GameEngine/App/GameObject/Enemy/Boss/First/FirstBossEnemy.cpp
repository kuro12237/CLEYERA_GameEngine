#include "FirstBossEnemy.h"


#include <Enemy/Boss/Behavior/BossEnemySelector.h>
#include "Enemy/Boss/Behavior/BossEnemySequence.h"
#include <Enemy/Boss/Behavior/BossEnemyTracking.h>
#include <Enemy/Boss/Behavior/BossEnemyIsPlayerInRange.h>
#include <Enemy/Boss/Behavior/BossEnemyNoneBehavior.h>


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
   translate_ = {.x = 5.0f, .y = 0.5f, .z = 15.0f};

   //ルート
   std::unique_ptr<BossEnemySelector> root = std::make_unique<BossEnemySelector>();

#pragma region シーケンス
   std::unique_ptr<BossEnemySequence> approachSeq = std::make_unique<BossEnemySequence>();
   //プレイヤーが設定した範囲内にいるかどうか
   approachSeq->AddChild(std::make_unique<BossEnemyIsPlayerInRange>(40.0f));
   //追跡
   approachSeq->AddChild(std::make_unique<BossEnemyTracking>());
   //作ったものを入れる
   root->AddChild(std::move(approachSeq));
#pragma endregion

   //無し
   root->AddChild(std::make_unique<BossEnemyNoneBehavior>());



   //本体に入れていく
   behaviorTree_ = std::move(root);

}

void FirstBossEnemy::Update() {

	//ビヘイビアツリーの実行
	behaviorTree_->Execute(this);
	const float_t SPEED = 0.1f;
	velocity_.x *= SPEED;
	velocity_.z *= SPEED;


	// 更新
   TransformUpdate();


#ifdef _DEBUG
   std::string condition = behaviorTree_->GetConditionName();

   ImGui::Begin("FirstBoss");
   ImGui::Text(condition.c_str());
   ImGui::InputFloat3("Translate", &translate_.x);
   ImGui::InputFloat3("Velocity", &velocity_.x);
   ImGui::End();

#endif // _DEBUG


}
