#include "BakugekiSnipeBossEnemyBullet2.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void BakugekiSnipeBossEnemyBullet2::Initialize(const Math::Vector::Vec3 &enemyPosition,
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
  bossEnemyPosition_ = enemyPosition;
  translate_ = bossEnemyPosition_;
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

void BakugekiSnipeBossEnemyBullet2::Update() {
    // 最大5秒まで表示その後に消える
    displayTime_ += DELTA_TIME_;
    if ( displayTime_ > MAX_DISPLAY_TIME_ ) {
        isDelete_ = true;
    }

    // 座標の加算

    translate_ += direction_ * SPEED_;

    // 更新
    TransformUpdate();
}

void BakugekiSnipeBossEnemyBullet2::OnCollision(std::weak_ptr<ObjectComponent> other) {

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
