#include "PlayerDemoSignatureBullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerDemoSignatureBullet::PlayerDemoSignatureBullet() {}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerDemoSignatureBullet::Init() {

  // クラス名
  ObjectComponent::name_ = VAR_NAME(PlayerDemoSignatureBullet);

  // Modelの設定
  uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
                                                              "PlayerDemoBullet");
  ObjectComponent::gameObject_->ChangeModel(handle);

  // ForceからY軸を求める
  CalcRotateFromVelocity();

  // 生存時間を適当に設定 1秒
  lifeTime_ = 3.0f * 60.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerDemoSignatureBullet::Update() {

  ObjectComponent::TransformUpdate();
  IPlayerBullet::Update_LifeTime();

  // 移動処理
  Move();
}

/// <summary>
/// 移動処理
/// </summary>
void PlayerDemoSignatureBullet::Move() { force_ = initVel_; }