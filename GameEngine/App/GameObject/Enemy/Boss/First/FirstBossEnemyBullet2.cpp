#include "FirstBossEnemyBullet2.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void FirstBossEnemyBullet2::Initialize(const Math::Vector::Vec3 &enemyPosition,
                                    const Math::Vector::Vec3 &playerPosition) {
  // 名前の設定
  name_ = VAR_NAME(NormalEnemy1Bullet);

  // モデルの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
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
  collider_->SetHitCallFunc(
      [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

  //攻撃力
  attackPower_ = std::make_unique<AttackPower>();
  attackPower_->Init();
  //jsonで変更できるように
  attackPower_->SetPower(10);

}

void FirstBossEnemyBullet2::Update() {
  // 時間
  aliveTime_ += DELTA_TIME_;
  if (aliveTime_ > DELETE_TIME_) {
    isDelete_ = true;
  }

  // 線形補間でXZ
  t_ += 1.0f / (ATTACK_ALL_TIME_ * FPS_VALUE_);
  t_ = std::clamp(t_, 0.0f, 1.0f);
  float_t startY = normalEnemyPosition_.y;
  float_t endY = playerPosition_.y;
  float_t baseY = std::lerp(startY, endY, t_);

  translate_.x = Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).x;
  translate_.y = sin(t_ * std::numbers::pi_v<float_t>) * HEIGHT_ + baseY;
  translate_.z = Math::Vector::Func::Lerp(normalEnemyPosition_, playerPosition_, t_).z;

  // 更新
  TransformUpdate();

}

void FirstBossEnemyBullet2::OnCollision(std::weak_ptr<ObjectComponent> other) {

  auto obj = other.lock();

  if (!obj) {
    return;
  }

  // Wall 型にキャストできるかをチェック
  if (auto wall = std::dynamic_pointer_cast<Wall>(obj)) {

    isDelete_ = true;
  }

  if (auto enemyBullet = std::dynamic_pointer_cast<PlayerCore>(obj)) {

    isDelete_ = true;
  }
}
