#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

/* プレイヤーの攻撃の覇者物クラス */
class IPlayerBullet : public CLEYERA::Component::ObjectComponent {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  IPlayerBullet() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~IPlayerBullet() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override {}

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

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
};