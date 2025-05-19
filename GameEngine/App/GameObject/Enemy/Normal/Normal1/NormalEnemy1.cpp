#include "NormalEnemy1.h"


#include "Enemy/Normal/Behavior/NormalEnemySelector.h"
#include "Enemy/Normal/Behavior/NormalEnemySequence.h"
#include "Enemy/Normal/Behavior/NormalEnemyTracking.h"
#include "Enemy/Normal/Behavior/NormalEnemyIsPlayerInRange.h"
#include "Enemy/Normal/Behavior/NormalEnemyNoneBehavior.h"
#include "Enemy/Normal/Behavior/NormalEnemyAttack.h"

void NormalEnemy1::Init() {
   // 名前の設定
   name_ = VAR_NAME(FirstBossEnemy);

   // モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Sphere","Sphere");
   gameObject_->ChangeModel(modelHandle);

   // コライダー作成
   CreateCollider(ColliderType::OBB);

   //スケールの設定
   scale_ = {.x = 1.0f, .y = 1.0f, .z = 1.0f};
   translate_.y = 0.5f;

   //ルート
   std::unique_ptr<NormalEnemySelector> root = std::make_unique<NormalEnemySelector>();

#pragma region 攻撃シーケンス
	std::unique_ptr<NormalEnemySequence> attackSequence = std::make_unique<NormalEnemySequence>();
	//プレイヤーが設定した範囲内にいるかどうか(攻撃用)
	attackSequence->AddChild(std::make_unique<NormalEnemyIsPlayerInRange>(ATTACK_START_DISTANCE_));
	//攻撃
	attackSequence->AddChild(std::make_unique<NormalEnemyAttack>());
	root->AddChild(std::move(attackSequence));
#pragma endregion

#pragma region 通常状態のシーケンス
   std::unique_ptr<NormalEnemySequence> approachSequence = std::make_unique<NormalEnemySequence>();
   //プレイヤーが設定した範囲内にいるかどうか
   approachSequence->AddChild(std::make_unique<NormalEnemyIsPlayerInRange>(TRACKING_START_DISTANCE_));
   //追跡
   approachSequence->AddChild(std::make_unique<NormalEnemyTracking>());
   //作ったものを入れる
   root->AddChild(std::move(approachSequence));
#pragma endregion

   //本体に入れていく
   behaviorTree_ = std::move(root);

}

void NormalEnemy1::Update() {

	//ビヘイビアツリーの実行
	behaviorTree_->Execute(this);
	const float_t SPEED = 0.1f;
	velocity_.x *= SPEED;
	velocity_.z *= SPEED;

	// 更新
   TransformUpdate();


#ifdef _DEBUG
   //ImGui表示用
   DisplayImGui();

#endif // _DEBUG


}

void NormalEnemy1::DisplayImGui(){
	ImGui::Begin("NormalEnemy1");
	ImGui::InputFloat3("Translate", &translate_.x);
	ImGui::InputFloat3("Velocity", &velocity_.x);
	ImGui::End();
}
