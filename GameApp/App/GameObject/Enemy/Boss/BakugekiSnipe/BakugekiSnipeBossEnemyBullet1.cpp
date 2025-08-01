#include "BakugekiSnipeBossEnemyBullet1.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void BakugekiSnipeBossEnemyBullet1::Initialize(const Math::Vector::Vec3 &enemyPosition,
                                    const Math::Vector::Vec3 &playerPosition) {

  // モデルの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Bullet/NormalBullet", "NormalBullet");
  gameObject_->ChangeModel(modelHandle);

  // コライダー作成
  CreateCollider(ColliderType::AABB);

  isGravity_ = false;
  // スケールの設定
  scale_ = {.x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_};
  translate_ = enemyPosition;

  // 方向を決める
  direction_ = playerPosition - translate_;
  direction_ = Math::Vector::Func::Normalize(direction_);

  // あたりはんてい関数セット
  collider_->SetHitCallFunc(
      [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });


  // 攻撃力
  attackPower_ = std::make_unique<AttackPower>();
  attackPower_->Init();
  // jsonで変更できるように
  attackPower_->SetPower(10);
}

void BakugekiSnipeBossEnemyBullet1::Update() {

  // 最大5秒まで表示その後に消える
  displayTime_ += DELTA_TIME_;
  if (displayTime_ > MAX_DISPLAY_TIME_) {
    isDelete_ = true;
  }

  // 座標の加算
  translate_ += direction_ * SPEED_;

  // 更新
  TransformUpdate();

}

void BakugekiSnipeBossEnemyBullet1::OnCollision(std::weak_ptr<ObjectComponent> other) {

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

