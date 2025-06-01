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
  void Update() override {}

#pragma region Accessor

  // ワールド座標の取得
  inline Math::Vector::Vec3 GetWorldPos() const {
    return ObjectComponent::gameObject_->GetWorldPos();
  }

  // 座標の設定
  inline void SetPosition(const Math::Vector::Vec3 &pos) { translate_ = pos; }

  // 速度の設定
  inline void SetVelocity(const Math::Vector::Vec3 &vel) { force_ = vel; }

  // 起動中か
  inline bool IsActive() const { return isActive_; }

  // 起動時間の設定
  inline void SetLifeTime(float time) { lifeTime_ = time; }

#pragma endregion

private:
  float lifeTime_ = 0.0f; // 生存期間 (秒)
  float damage_ = 0.0f; // ダメージ量
  bool isActive_ = true; // アクティブかどうか
};