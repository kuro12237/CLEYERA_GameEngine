#include "FirstBossEnemy.h"


#include "Enemy/Boss/Behavior/BossEnemySelector.h"
#include "Enemy/Boss/Behavior/BossEnemySequence.h"
#include "Enemy/Boss/Behavior/BossEnemyTracking.h"
#include "Enemy/Boss/Behavior/BossEnemyIsPlayerInRange.h"
#include "Enemy/Boss/Behavior/BossEnemyNoneBehavior.h"
#include "Enemy/Boss/Behavior/BossEnemyAttack.h"
#include "Enemy/Boss/Behavior/BossEnemyIsEnraged.h"
#include "Enemy/Boss/Behavior/BossEnemyRandomAttackSelector.h"
#include <Enemy/Boss/Behavior/BossEnemyMagicAttack.h>
#include <Enemy/Boss/Behavior/BossEnemyThrustAttack.h>

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

#pragma region 攻撃シーケンス
	std::unique_ptr<BossEnemySequence> attackSequence = std::make_unique<BossEnemySequence>();
	//プレイヤーが設定した範囲内にいるかどうか(攻撃用)
	attackSequence->AddChild(std::make_unique<BossEnemyIsPlayerInRange>(5.0f));
	// ランダム攻撃セレクタ
	std::unique_ptr<BossEnemyRandomAttackSelector> attackSelector = std::make_unique<BossEnemyRandomAttackSelector>();
	attackSelector->AddChild(std::make_unique<BossEnemyMagicAttack>());
	attackSelector->AddChild(std::make_unique<BossEnemyThrustAttack>());
	attackSelector->AddChild(std::make_unique<BossEnemyAttack>());
	attackSequence->AddChild(std::move(attackSelector));
	root->AddChild(std::move(attackSequence));

#pragma endregion

#pragma region 通常状態のシーケンス
   std::unique_ptr<BossEnemySequence> approachSequence = std::make_unique<BossEnemySequence>();
   //プレイヤーが設定した範囲内にいるかどうか
   approachSequence->AddChild(std::make_unique<BossEnemyIsPlayerInRange>(trackingStartDistance_));
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


   hp_->SetName(this->name_);
   hp_->Init();
}

void FirstBossEnemy::Update() {

	// hp処理
  hp_->Update();
  if (hp_->GetIsDead()) {
    // 倒された
    isAlive_ = false;
    Killed();
  }

  if (isAlive_ == true) {
    // 弾の更新
    for (const std::shared_ptr<BaseBossEnemyBullet> &bullet : bullets_) {
      bullet->Update();
    }

    // 弾の削除
    bullets_.remove_if([](const auto &bullet) { return bullet->GetIsDelete(); });

    // 向きを計算しモデルを回転させる
    float_t directionToRotateY = std::atan2f(-direction_.z, direction_.x);
    // 回転のオフセット
    // 元々のモデルの回転が変だったのでこれを足している
    const float_t ROTATE_OFFSET = -std::numbers::pi_v<float_t> / 2.0f;
    rotate_.y = directionToRotateY + ROTATE_OFFSET;

    // ビヘイビアツリーの実行
    behaviorTree_->Execute(this);
    // atan2 で回転角を求める（ラジアン）
    float_t angle = std::atan2(-direction_.z, direction_.x);
    // 角度を敵の回転に設定
    rotate_.y = angle - std::numbers::pi_v<float_t> / 2.0f;
    // 速度を計算
    Math::Vector::Vec3 newDirection = {};
    if (isAttack_ == false) {
      newDirection = direction_;
    }

    velocity_ = newDirection * speed_;

    // 体力無し
    if (parameter_.hp_ <= 0) {
      isAlive_ = false;
    }

    // プレイヤーへの方向を計算
    directionToPlayer_ = Math::Vector::Func::Normalize(playerPosition_ - translate_);

    // ノックバック
    KnockBack();
  }
	// 更新
   TransformUpdate();



}

void FirstBossEnemy::ImGuiUpdate() {
#ifdef _DEBUG
  ImGui::Begin("FirstBoss");
  ImGui::InputFloat3("Translate", &translate_.x);
  ImGui::InputFloat3("Velocity", &velocity_.x);
  ImGui::End();

#endif // _DEBUG



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

void FirstBossEnemy::KnockBack() {

}

void FirstBossEnemy::Killed() {

}
