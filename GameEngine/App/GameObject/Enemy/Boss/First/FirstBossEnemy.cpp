#include "FirstBossEnemy.h"
#include <Enemy/Boss/Behavior/BossEnemySelector.h>
#include "Enemy/Boss/Behavior/BossEnemySequence.h"
#include <Enemy/Boss/Behavior/BossEnemyTracking.h>


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










   auto root = std::make_unique<BossEnemySelector>();

   // 遠距離 → 近づく
   auto approachSeq = std::make_unique<BossEnemySequence>();
  // approachSeq->AddChild(std::make_unique<IsPlayerFar>());
   approachSeq->AddChild(new BossEnemyTracking());

   // 近距離 → 攻撃
   auto attackSeq = std::make_unique<BossEnemySequence>();
   attackSeq->AddChild(std::make_unique<IsPlayerNear>());
   attackSeq->AddChild(std::make_unique<AttackPlayer>());

   root->AddChild(std::move(approachSeq));
   root->AddChild(std::move(attackSeq));

   behaviorTree_ = std::move(root);

}

void FirstBossEnemy::Update() {


	//方向を取得
   const float_t SPEED = 0.005f;
   velocity_.x = (playerPosition_.x - translate_.x) * SPEED;
   velocity_.z = (playerPosition_.z - translate_.z) * SPEED;

	// 更新
   TransformUpdate();
}
