#include "GunNormalEnemyBullet.h"
#include "Player/Core/playerCore.h"
#include "Wall/Wall.h"

void GunNormalEnemyBullet::Initialize(const Math::Vector::Vec3 &enemyPosition,const Math::Vector::Vec3 &playerPosition,const bool &isPersistentlyTrack) {

  // モデルの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Bullet/NormalBullet", "NormalBullet");
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

void GunNormalEnemyBullet::Update() {

  // 最大5秒まで表示その後に消える
  displayTime_ += DELTA_TIME_;
  if (displayTime_ > MAX_DISPLAY_TIME_) {
    isDelete_ = true;
    mode_ = CLEYERA::Component::ObjectComponent::OBJ_MODE::REMOVE;
  }

  //向きを計算
  Math::Vector::Vec3 direction = Math::Vector::Func::Normalize(playerPosition_ - translate_);
  rotate_.y = std::atan2f(direction.x, direction.z);
  // 座標の加算
  translate_ += direction_ * SPEED_;

  // 更新
  TransformUpdate();

#ifdef _DEBUG
  DisplayImGui();
#endif // _DEBUG
}

void GunNormalEnemyBullet::OnCollision(std::weak_ptr<ObjectComponent> other) {

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

void GunNormalEnemyBullet::DisplayImGui() {
  /*ImGui::Begin("Bullet2");
  ImGui::InputFloat3("Direction", &direction_.x);
  ImGui::InputFloat3("Position", &translate_.x);
  ImGui::End();*/
}
