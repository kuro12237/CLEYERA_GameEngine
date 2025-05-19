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
  float_t distance = Math::Vector::Func::Length(GetPosition() -
                                                GetPlayerPosition());


  // 方向を求める
  Math::Vector::Vec3 velocity = GetPlayerPosition() - GetPosition();



	//攻撃していない時
  if (isAttack_ == false) {
    
    // 攻撃範囲内の時
    if (distance < GetAttackStartDistance()) {

      // 弾
      std::unique_ptr<NormalEnemyBullet> bullet = std::make_unique<NormalEnemyBullet>();
      bullet->Init();
      // 挿入
      bullets_.push_back(std::move(bullet));

      isAttack_ = true;
    } else if (distance >= GetAttackStartDistance()&& distance < TRACKING_START_DISTANCE_) {
      

      // 本体に設定
      SetVelocity(Math::Vector::Func::Normalize(velocity));

    }
  }

	// 弾の更新
  for (const auto &bullet : bullets_) {
    bullet->SetNormalEnemyPosition(GetPosition());
    bullet->SetPlayerPosition(GetPlayerPosition());
    bullet->Update();
  }

  // 弾の削除
  bullets_.remove_if([](const auto &bullet) { return bullet->GetIsDelete(); });

  if (isAttack_ == true && bullets_.empty()) {
    isAttack_ = false;
  }


	//ビヘイビアツリーの実行
	////behaviorTree_->Execute(this);
	const float_t SPEED = 0.1f;
	velocity_.x *= SPEED;
        velocity_.y *= SPEED;
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
