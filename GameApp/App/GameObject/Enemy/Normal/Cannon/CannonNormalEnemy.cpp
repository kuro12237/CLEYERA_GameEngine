#include "CannonNormalEnemy.h"

#include "Utility/Easing.h"

#include "Enemy/Normal/Behavior/NormalEnemyAttack.h"
#include "Enemy/Normal/Behavior/NormalEnemyIsPlayerInAttackRange.h"
#include "Enemy/Normal/Behavior/NormalEnemyIsPlayerInRange.h"
#include "Enemy/Normal/Behavior/NormalEnemyNoneBehavior.h"
#include "Enemy/Normal/Behavior/NormalEnemySelector.h"
#include "Enemy/Normal/Behavior/NormalEnemySequence.h"
#include "Enemy/Normal/Behavior/NormalEnemyTracking.h"

#include "../../../Player/Attack/Interface/IPlayerBullet.h"

void CannonNormalEnemy::Init() {
  // 名前の設定
  name_ = VAR_NAME(CannonNormalEnemy);

  // モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/enemy", "enemy");
  gameObject_->ChangeModel(modelHandle);

  // これが無いと描画エラーになる
  uint32_t modelHandle2 =
      modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
  modelHandle2;

  // コライダー作成
  CreateCollider(ColliderType::AABB);

  // スケールの設定
  scale_ = {.x = 1.0f, .y = 1.0f, .z = 1.0f};

  // 体力
  parameter_.maxHp_ = 3u;
  parameter_.hp_ = parameter_.maxHp_;
  // ノックバックの距離
  parameter_.knockBackDistance_ = 1.0f;
  // ルート
  std::unique_ptr<NormalEnemySelector> root =
      std::make_unique<NormalEnemySelector>();

  // 追跡開始距離
  trackingStartDistance_ = 40.0f;
  // 攻撃開始距離
  attackStartDistance_ = 10.0f;

#pragma region 攻撃シーケンス
  std::unique_ptr<NormalEnemySequence> attackSequence =
      std::make_unique<NormalEnemySequence>();
  // プレイヤーが設定した範囲内にいるかどうか(攻撃用)
  attackSequence->AddChild(
      std::make_unique<NormalEnemyIsPlayerInAttackRange>());
  // 攻撃
  attackSequence->AddChild(
      std::make_unique<NormalEnemyAttack>(BulletType::NormalCannonBullet, 1u, 3.0f));
  root->AddChild(std::move(attackSequence));
#pragma endregion

#pragma region 通常状態のシーケンス
  std::unique_ptr<NormalEnemySequence> approachSequence =
      std::make_unique<NormalEnemySequence>();
  // プレイヤーが設定した範囲内にいるかどうか
  approachSequence->AddChild(
      std::make_unique<NormalEnemyIsPlayerInRange>(trackingStartDistance_));
  // 追跡
  approachSequence->AddChild(std::make_unique<NormalEnemyTracking>());
  // 作ったものを入れる
  root->AddChild(std::move(approachSequence));
#pragma endregion

  // 本体に入れていく
  behaviorTree_ = std::move(root);

  // あたりはんてい関数セット
  collider_->SetHitCallFunc([this](std::weak_ptr<ObjectComponent> other) {
    this->OnCollision(other);
  });

  
  hpGauge_=objectManager_->CreateObject<EnemyHPGauge>(
      "HPGauge", std::make_shared<EnemyHPGauge>());
  hpGauge_.lock()->Init();
  hpGauge_.lock()->SetBaseEnemy(this);

  hpJsonDirectory_ = name_;
  hp_->SetName(this->name_);
  hp_->Init();

}

void CannonNormalEnemy::Update() {

    // hp処理
    hp_->Update();
    
    if (hp_->GetIsDead()) {
        isAlive_ = false;
        // 倒された
        Killed();
    }


    int a = 0;
    if ( isDelete_ == true ) {
        a++;
    }

    //HPゲージ
    hpGauge_.lock()->Update();

    // 生存時
    if (isAlive_ == true) {
        // クールタイム中
        if (isCool_ == true) {
            coolTime_ += DELTA_TIME_;
            if (coolTime_ > coolTimeLimit_) {
                isCool_ = false;
                coolTime_ = 0.0f;
                generateBulletNumber_ = 0u;
            }
        }

        for (auto it = bullets_.begin(); it != bullets_.end();) {
            if (it->expired()) {
                it = bullets_.erase(it); // expiredならeraseして次に進む
                continue;
            }

            auto sp = it->lock();
            if (sp && sp->GetIsDelete()) {
                sp->SetMode(CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE);
            }

            ++it;
        }


        // 向きを計算しモデルを回転させる
        float_t directionToRotateY = std::atan2f(-direction_.z, direction_.x);
        // 回転のオフセット
        // 元々のモデルの回転が変だったのでこれを足している
        const float_t ROTATE_OFFSET = -std::numbers::pi_v<float_t> / 2.0f;
        rotate_.y = directionToRotateY + ROTATE_OFFSET;

        // ビヘイビアツリーの実行
        behaviorTree_->Execute(this);

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

void CannonNormalEnemy::ImGuiUpdate() {

  if (ImGui::TreeNode(name_.c_str())) {

    // 基礎機能の表示
    this->BaseParamImGuiDisply();

    if (ImGui::TreeNode("KnockBack") == true) {
      ImGui::InputFloat3("DirectionToPlayer", &directionToPlayer_.x);
      ImGui::InputFloat("T", &knockbackT_);
      ImGui::InputFloat3("BeforePosition", &beforeKnockBackPosition_.x);
      ImGui::InputFloat3("AfterPosition", &afterKnockBackPosition_.x);
      ImGui::TreePop();
    }

    if (ImGui::TreeNode("Parameter") == true) {
      ImGui::SliderInt("MaxHP", &parameter_.maxHp_, 0, 10);
      ImGui::SliderInt("HP", &parameter_.hp_, 0, 10);
      ImGui::SliderFloat("MaxHP", &parameter_.knockBackDistance_, 0.0, 5.0f);
      ImGui::TreePop();
    }

    ImGui::Checkbox("isKnockBack", &isKnockBack_);
    ImGui::InputFloat3("Scele", &scale_.x);
    ImGui::Checkbox("IsAlive", &isAlive_);
    ImGui::Checkbox("IsDelete", &isDelete_);
    ImGui::InputFloat3("Translate", &translate_.x);
    ImGui::InputFloat3("Velocity", &velocity_.x);

    hp_->ImGuiUpdate();

    ImGui::TreePop();
  }
}

void CannonNormalEnemy::OnCollision(std::weak_ptr<ObjectComponent> other) {

  auto obj = other.lock();

  if (!obj) {
    return;
  }
  // Wall 型にキャストできるかをチェック
  if (auto wall = std::dynamic_pointer_cast<Wall>(obj)) {
    // Wall にぶつかったときの処理
    auto aabb =
        std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(wall);
    // 押し出し
    // this->translate_ -= aabb->GetAABB().push;
  }

  // Player型にキャストできるかをチェック
  if (auto p = std::dynamic_pointer_cast<IPlayerBullet>(obj)) {
    // Player にぶつかったときの処理
    hp_->CalcHp(p->GetAttackPower());
  }
}

void CannonNormalEnemy::KnockBack() {

  // ランダムの値で位置を決める
  // SRは固定
  std::uniform_real_distribution<float_t> distribute(-1.0f, 1.0f);
  // ランダムエンジン
  std::random_device seedGenerator;
  std::mt19937 randomEngine(seedGenerator());
  if (isKnockBack_ == true) {
    Math::Vector::Vec3 knockBackDirection = {};
    if (isDesidePosition_ == false) {
      knockBackDirection = {.x = (1.0f - directionToPlayer_.x),
                            .y = 0.0f,
                            .z = (1.0f - directionToPlayer_.z)};
      beforeKnockBackPosition_ = translate_;
      afterKnockBackPosition_ =
          beforeKnockBackPosition_ +
          knockBackDirection * parameter_.knockBackDistance_;
      isDesidePosition_ = true;
    }

    // ノックバックの時間
    knockBackTime_ += DELTA_TIME_;
    // 線形補間
    knockbackT_ += INCREASE_T_VALUE_;
    // 座標を線形補間でやるよ！
    translate_ = Math::Vector::Func::Lerp(beforeKnockBackPosition_,
                                          afterKnockBackPosition_, knockbackT_);
    knockbackT_ = std::clamp(knockbackT_, 0.0f, 1.0f);

    // 制限を超えたら0に戻る
    if (knockbackT_ >= 1.0f && knockBackTime_ > MAX_KNOCK_BACK_TIME_) {
      knockBackTime_ = 0.0f;
      knockbackT_ = 0.0f;
      isKnockBack_ = false;
      isDesidePosition_ = false;
    }
  }
}

void CannonNormalEnemy::Killed() {
  if (isAlive_ == false) {
    // 縮小
    const float_t SCALE_DOWN = 0.05f;
    scale_ -= {SCALE_DOWN, SCALE_DOWN, SCALE_DOWN};

    if (scale_.x < 0.0f) {
      // スケール固定
      scale_.x = 0.0f;
      scale_.y = 0.0f;
      scale_.z = 0.0f;
      // 消す
      isDelete_ = true;
    }
  }
}