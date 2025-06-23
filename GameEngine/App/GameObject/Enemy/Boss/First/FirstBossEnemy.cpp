#include "FirstBossEnemy.h"


#include "Enemy/Boss/Behavior/BossEnemySelector.h"
#include "Enemy/Boss/Behavior/BossEnemySequence.h"
#include "Enemy/Boss/Behavior/BossEnemyTracking.h"
#include "Enemy/Boss/Behavior/BossEnemyIsPlayerInRange.h"
#include "Enemy/Boss/Behavior/BossEnemyIsEnraged.h"
#include "Enemy/Boss/Behavior/BossEnemyRandomAttackSelector.h"
void FirstBossEnemy::Init() {
   // 名前の設定
   name_ = VAR_NAME(FirstBossEnemy);

   // モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/system/Sphere","Sphere");
   gameObject_->ChangeModel(modelHandle);

   // コライダー作成
   CreateCollider(ColliderType::OBB);

   //スケールの設定
   scale_ = {.x = 3.0f, .y = 3.0f, .z = 3.0f};
   // 座標の設定
   translate_ = {.x = 5.0f, .y = 0.5f, .z = 15.0f};

   //ルート
   std::unique_ptr<BossEnemySelector> root = std::make_unique<BossEnemySelector>();

#pragma region 攻撃シーケンス
	std::unique_ptr<BossEnemySequence> attackSequence = std::make_unique<BossEnemySequence>();
	//プレイヤーが設定した範囲内にいるかどうか(攻撃用)
	attackSequence->AddChild(std::make_unique<BossEnemyIsPlayerInRange>(5.0f));
	// ランダム攻撃セレクタ
	std::unique_ptr<BossEnemyRandomAttackSelector> attackSelector = std::make_unique<BossEnemyRandomAttackSelector>();
	attackSequence->AddChild(std::move(attackSelector));
	root->AddChild(std::move(attackSequence));

#pragma endregion

#pragma region 通常状態のシーケンス
   std::unique_ptr<BossEnemySequence> approachSequence = std::make_unique<BossEnemySequence>();
   //プレイヤーが設定した範囲内にいるかどうか
   approachSequence->AddChild(std::make_unique<BossEnemyIsPlayerInRange>(40.0f));
   //追跡
   approachSequence->AddChild(std::make_unique<BossEnemyTracking>());
   //作ったものを入れる
   root->AddChild(std::move(approachSequence));
#pragma endregion



   //本体に入れていく
   behaviorTree_ = std::move(root);

    // あたりはんてい関数セット
   collider_->SetHitCallFunc(
       [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

}

void FirstBossEnemy::Update() {

	//ビヘイビアツリーの実行
	//behaviorTree_->Execute(this);
	const float_t SPEED = 0.1f;
	velocity_.x *= SPEED;
	velocity_.z *= SPEED;


	// 更新
   TransformUpdate();





}

void FirstBossEnemy::ImGuiUpdate() {
#ifdef _DEBUG
  if (ImGui::TreeNode(name_.c_str()) == true) {
    ImGui::InputFloat3("Translate", &translate_.x);
    ImGui::InputFloat3("Velocity", &velocity_.x);
    ImGui::TreePop();
  }
  

#endif // _DEBUG
}

void FirstBossEnemy::KnockBack() {

}

void FirstBossEnemy::Killed() {


}



void FirstBossEnemy::OnCollision(std::weak_ptr<ObjectComponent> other) {
  other;
  //if (auto obj = other.lock()) {
  //  // Wall 型にキャストできるかをチェック
  //  if (auto wall = std::dynamic_pointer_cast<Wall>(obj)) {
  //    // Wall にぶつかったときの処理
  //    auto aabb = std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(
  //        wall->GetCollder().lock());
  //    // 押し出し
  //    this->translate_ -= aabb->GetAABB().push;
  //  }
  //}
}