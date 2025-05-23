#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

/* プレイヤーの攻撃の覇者物クラス */
class PlayerProjectile : public CLEYERA::Component::ObjectComponent {

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerProjectile() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerProjectile() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override;

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
  void SetPosition(const Math::Vector::Vec3& pos) { translate_ = pos; }

  // 速度の設定
  void SetVelocity(const Math::Vector::Vec3 &vel) { force_ = vel; }

  // 生存時間の設定
  void SetLifeTime(float time) { lifeTime_ = time; }

#pragma endregion


public:

  float lifeTime_;       // 生存期間 (秒)
  int damage_;           // ダメージ量
  bool isActive_ = true; // アクティブかどうか
};