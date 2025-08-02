#include "CannonNormalEnemy1Bullet.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void CannonNormalEnemy1Bullet::Initialize(
    const Math::Vector::Vec3 &enemyPosition,
    const Math::Vector::Vec3 &playerPosition, const bool &isPersistentlyTrack) {
  isGravity_ = false;
  // モデルの設定
  uint32_t modelHandle =
      modelManager_->LoadModel("Resources/Model/Bullet/NormalBullet", "NormalBullet");
  gameObject_->ChangeModel(modelHandle);

  // コライダー作成
  CreateCollider(ColliderType::AABB);
  // スケールの設定
  scale_ = {.x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_};
  // 本体の座標を設定
  normalEnemyPosition_ = enemyPosition;
  translate_ = normalEnemyPosition_;
  // プレイヤーの座標を設定
  playerPosition_ = playerPosition;

  // あたりはんてい関数セット
  collider_->SetHitCallFunc([this](std::weak_ptr<ObjectComponent> other) {
    this->OnCollision(other);
  });

  isPersistentlyTrack_ = isPersistentlyTrack;

  // 攻撃力
  attackPower_ = std::make_unique<AttackPower>();
  attackPower_->Init();
  // jsonで変更できるように
  attackPower_->SetPower(10);
}

void CannonNormalEnemy1Bullet::Update() {
  // 時間
  aliveTime_ += DELTA_TIME_;
  // 線形補間でXZ
  t_ += 1.0f / (ATTACK_ALL_TIME_ * FPS_VALUE_);
  t_ = std::clamp(t_, 0.0f, 1.0f);
  float_t startY = normalEnemyPosition_.y;
  float_t endY = playerPosition_.y;
  float_t baseY = std::lerp(startY, endY, t_);

  if (t_ >= 1.0f) {
    isDelete_;
    mode_ = CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE;
  }

  //向きを計算
  Math::Vector::Vec3 direction = Math::Vector::Func::Normalize(playerPosition_ - translate_);
  rotate_.y = std::atan2f(direction.x, direction.z);
  //座標の計算
  translate_.x =Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).x;
  translate_.y = baseY + sinf(t_ * std::numbers::pi_v<float_t>);
  translate_.z = Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).z;

#ifdef _DEBUG
  ImGui::Begin("Cannon");
  ImGui::InputFloat3("Translate", &translate_.x);
  ImGui::InputFloat("BaseY", &baseY);
  ImGui::InputFloat("T", &t_);

  ImGui::InputFloat3("PlayerPosition", &playerPosition_.x);
  ImGui::InputFloat3("EnemyPosition", &normalEnemyPosition_.x);
  ImGui::End();
#endif // _DEBUG

  // 更新
  TransformUpdate();
}

void CannonNormalEnemy1Bullet::OnCollision(
    std::weak_ptr<ObjectComponent> other) {

  auto obj = other.lock();

  if (!obj) {
    return;
  }

  // Wall 型にキャストできるかをチェック
  if (auto wall = std::dynamic_pointer_cast<Wall>(obj)) {

    isDelete_ = true;

    mode_ = CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE;
  }

  if (auto enemyBullet = std::dynamic_pointer_cast<PlayerCore>(obj)) {

    isDelete_ = true;
    mode_ = CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE;
  }
}
