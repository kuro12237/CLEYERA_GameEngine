#include "PlayerDemoBullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerDemoBullet::PlayerDemoBullet() {}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerDemoBullet::Init() {

  // クラス名
  ObjectComponent::name_ = VAR_NAME(PlayerDemoBullet);

  // Modelの設定
  uint32_t handle = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
                                                              "PlayerDemoBullet");
  ObjectComponent::gameObject_->ChangeModel(handle);

  // 生存時間を適当に設定 1秒
  lifeTime_ = 1.0f * 60.0f;

  // ForceからY軸を求める
  CalcRotateFromVelocity();
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerDemoBullet::Update() {
  ObjectComponent::TransformUpdate();
  IPlayerBullet::Update_LifeTime();
  force_ = initVel_;
}
