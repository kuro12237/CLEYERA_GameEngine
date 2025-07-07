#include "NormalEnemy3Bullet.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void NormalEnemy3Bullet::Initialize(const Math::Vector::Vec3 &enemyPosition,
                                    const Math::Vector::Vec3 &playerPosition,
                                    const bool &isPersistentlyTrack) {
  // 名前の設定
  name_ = VAR_NAME(NormalEnemyBullet);

  // モデルの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/enemyBullet", "enemyBullet");
  gameObject_->ChangeModel(modelHandle);

  // コライダー作成
  CreateCollider(ColliderType::AABB);

  // スケールの設定
  scale_ = {.x = SCALE_SIZE_, .y = SCALE_SIZE_, .z = SCALE_SIZE_};
  translate_ = enemyPosition;

  // 方向を決める
  direction_ = playerPosition - translate_;
  direction_ = Math::Vector::Func::Normalize(direction_);

  auto aabb = std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(collider_);

  aabb->SetSize({-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f});

  // あたりはんてい関数セット
  collider_->SetHitCallFunc(
      [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });

  isPersistentlyTrack_ = isPersistentlyTrack;

  // 攻撃力
  attackPower_ = std::make_unique<AttackPower>();
  attackPower_->Init();
  // jsonで変更できるように
  attackPower_->SetPower(10);
}

void NormalEnemy3Bullet::Update() {

    // 最大5秒まで表示その後に消える
    displayTime_ += DELTA_TIME_;
    if (displayTime_ > MAX_DISPLAY_TIME_) {
        scale_.x -= SCALE_DOWN_VALUE_;
        scale_.y -= SCALE_DOWN_VALUE_;
        scale_.z -= SCALE_DOWN_VALUE_;
    }
    //スケールが0になったら消える
    if ( scale_.x <= DELETE_SCALE_ && 
        scale_.y <= DELETE_SCALE_ && 
        scale_.z <= DELETE_SCALE_ ) {
        isDelete_ = true;
    }

    //TRACKING_LIMIT_TIME_秒まで追跡
    trackingTime_ += DELTA_TIME_;
    if ( trackingTime_ < TRACKING_LIMIT_TIME_ ) {
        direction_ = Math::Vector::Func::Normalize(playerPosition_ - translate_);
    }
    
    // 座標の加算
    translate_ += direction_ * SPEED_;

    // 更新
    TransformUpdate();

}

void NormalEnemy3Bullet::OnCollision(std::weak_ptr<ObjectComponent> other) {

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
