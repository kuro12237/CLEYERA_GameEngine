#include "NormalEnemy2.h"


#include "Enemy/Normal/Behavior/NormalEnemySelector.h"
#include "Enemy/Normal/Behavior/NormalEnemySequence.h"
#include "Enemy/Normal/Behavior/NormalEnemyTracking.h"
#include "Enemy/Normal/Behavior/NormalEnemyIsPlayerInRange.h"
#include "Enemy/Normal/Behavior/NormalEnemyNoneBehavior.h"
#include "Enemy/Normal/Behavior/NormalEnemyAttack.h"
#include <Enemy/Normal/Behavior/NormalEnemyIsNotAttacking.h>
#include <Enemy/Normal/Behavior/NormalEnemyIsPlayerInAttackRange.h>

void NormalEnemy2::Init() {
   // 名前の設定
   name_ = VAR_NAME(NormalEnemy1);

   // モデルの設定
   uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Enemy2", "Enemy2");
   gameObject_->ChangeModel(modelHandle);

   // コライダー作成
   CreateCollider(ColliderType::OBB);

   //スケールの設定
   scale_ = {.x = 1.0f, .y = 1.0f, .z = 1.0f};

   //ルート
   //セレクターは一つでもSucceesすればいいよ
   std::unique_ptr<NormalEnemySelector> root = std::make_unique<NormalEnemySelector>();

    // 追跡開始距離
   trackingStartDistance_ = 70.0f;
   // 攻撃開始距離
   attackStartDistance_ = 15.0f;

   //シーケンスは全てSucceesしないとだめだよ
#pragma region 攻撃シーケンス
	std::unique_ptr<NormalEnemySequence> attackSequence = std::make_unique<NormalEnemySequence>();
    attackSequence->AddChild(std::make_unique<NormalEnemyIsPlayerInAttackRangeAndIsAttack>());
    attackSequence->AddChild(std::make_unique<NormalEnemyAttack>());
    root->AddChild(std::move(attackSequence));
#pragma endregion

#pragma region 通常状態のシーケンス
   //std::unique_ptr<NormalEnemySequence> approachSequence = std::make_unique<NormalEnemySequence>();
   ////プレイヤーが設定した範囲内にいるかどうか
   //approachSequence->AddChild(std::make_unique<NormalEnemyIsPlayerInRangeAndIsAttack>(trackingStartDistance_));
   ////追跡
   //approachSequence->AddChild(std::make_unique<NormalEnemyTracking>());
   ////作ったものを入れる
   //root->AddChild(std::move(approachSequence));
#pragma endregion

   //本体に入れていく
   behaviorTree_ = std::move(root);

  
}

void NormalEnemy2::Update() {
    //距離を求める
    //float_t distance = Math::Vector::Func::Length(GetWorldPosition() -GetPlayerPosition());
    // 方向を求める
    Math::Vector::Vec3 velocity = GetPlayerPosition() - GetWorldPosition();

	////攻撃していない時
    //if (isAttack_ == false) {
    //  
    //  // 攻撃範囲内の時
    //  if (distance < GetAttackStartDistance()) {
    //
    //    //// 弾
    //    std::shared_ptr<NormalEnemy2Bullet> bullet = std::make_shared<NormalEnemy2Bullet>();
    //    bullet->SetNormalEnemyPosition(GetWorldPosition());
    //    bullet->SetPlayerPosition(GetPlayerPosition());
    //    bullet->Init();
    //    // 挿入
    //    bullets_.push_back(std::move(bullet));
    //
    //    isAttack_ = true;
    //  } else if (distance >= GetAttackStartDistance() && distance < trackingStartDistance_) {
    //    
    //
    //    // 本体に設定
    //    SetVelocity(Math::Vector::Func::Normalize(velocity));
    //    
    //  }
    //}



    
    //正規化
    velocity= Math::Vector::Func::Normalize(velocity); 

    // atan2 で回転角を求める（ラジアン）
    float_t angle = std::atan2(-velocity.z, velocity.x); 

    // 角度を敵の回転に設定
    rotate_.y = angle-std::numbers::pi_v<float_t>/2.0f;

	//ビヘイビアツリーの実行
	behaviorTree_->Execute(this);
	//const float_t SPEED = 0.1f;
	//velocity_.x *= SPEED;
    //velocity_.y *= SPEED;
	//velocity_.z *= SPEED;

	// 更新
    TransformUpdate();

   	//// 弾の更新
    //for (const auto &bullet : bullets_) {
    //  bullet->Update();
    //}

    //// 弾の削除
    //bullets_.remove_if([](const auto &bullet) { return bullet->GetIsDelete(); });
    //
    //if (isAttack_ == true && bullets_.empty()) {
    //  isAttack_ = false;
    //}

#ifdef _DEBUG
    //ImGui表示用
    DisplayImGui();

#endif // _DEBUG


}

void NormalEnemy2::DisplayImGui() {
	ImGui::Begin("NormalEnemy2");
	ImGui::InputFloat3("Translate", &translate_.x);
	ImGui::InputFloat3("Velocity", &velocity_.x);
	ImGui::End();
}
