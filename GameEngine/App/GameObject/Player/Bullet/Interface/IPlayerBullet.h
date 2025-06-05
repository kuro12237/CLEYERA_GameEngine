#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "Component/AttackPower/AttackPower.h"


constexpr float BULLET_EPSILON = 0.001f;

/* プレイヤーの攻撃の覇者物クラス */
class IPlayerBullet : public CLEYERA::Component::ObjectComponent {

public:

  IPlayerBullet() {
    attackPower_ = std::make_unique<AttackPower>();
    // 仮設定
    attackPower_->SetPower(50);

    CreateCollider(ColliderType::AABB);
    auto aabb = std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(collider_);
    aabb->SetSize({-2.0f, -2.0f, -2.0f},{2.0f, 2.0f, 2.0f});
    collider_->SetHitCallFunc(
        [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });
  }

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~IPlayerBullet() = default;

  /// <summary>
  /// 衝突時コールバック
  /// </summary>
  virtual void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Accessor

  // ワールド座標の取得
  inline Math::Vector::Vec3 GetWorldPos() const {
    return ObjectComponent::gameObject_->GetWorldPos();
  }

  // 座標の設定
  inline void SetPosition(const Math::Vector::Vec3 &pos) { translate_ = pos; }

  // 速度の設定
  inline void SetVelocity(const Math::Vector::Vec3 &vel) { initVel_ = vel; }

  // 起動中か
  inline bool IsActive() const { return isActive_; }

  // 起動時間の設定
  inline void SetLifeTime(float time) { lifeTime_ = time; }

  int32_t GetAttackPower() { return this->attackPower_->GetPower(); }

#pragma endregion

protected:
  /// <summary>
  /// 生存時間の更新
  /// </summary>
  void Update_LifeTime() {
    lifeTime_--;
    if (lifeTime_ <= 0.0f) {
      lifeTime_ = 0.0f;
      isActive_ = false;
    }
  }

  /// <summary>
  /// VelocityからY軸回転を求める
  /// </summary>
  void CalcRotateFromVelocity() {
    rotate_.y = std::atan2(initVel_.x, initVel_.z);
    float velZ = std::sqrt((initVel_.x * initVel_.x) + (initVel_.z * initVel_.z));
    float height = -initVel_.y;
    rotate_.x = std::atan2(height, velZ);
  }

protected:
  float lifeTime_ = 0.0f; // 生存期間 (秒)
  float damage_ = 0.0f;   // ダメージ量
  bool isActive_ = true;  // アクティブかどうか
  Math::Vector::Vec3 initVel_{};

  std::unique_ptr<AttackPower> attackPower_ = nullptr;
};