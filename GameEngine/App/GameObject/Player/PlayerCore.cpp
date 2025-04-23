#include "PlayerCore.h"

using namespace CLEYERA;

void PlayerCore::Init() {
  // 基本クラス名をマクロ通して入れる
  name_ = VAR_NAME(PlayerCore);

  // modelの設定
  uint32_t modelHandle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
  gameObject_->ChangeModel(modelHandle);

  /// コライダー作成:現状OBB飲み
  CreateCollider(ColliderType::OBB);

  // jsonのファイル作成
  this->CreateJsonSystem("Player/");

  // jsonに読み書きする変数の設定
  SetValue<Math::Vector::Vec3>("t", translate_);
  translate_ = GetValue<Math::Vector::Vec3>("t");

  this->ChangeState(std::make_unique<PlayerMoveState>());

  // 当たった時のコールバック関数をセットラムダ使用
  collider_->SetHitCallFunc(
      [this](std::weak_ptr<CLEYERA::Component::ObjectComponent> other) { this->HitFunc(other); });
}

void PlayerCore::Update() {

  if (state_) {
    state_->Update();
  }

  TransformUpdate();
}

void PlayerCore::ChangeState(std::unique_ptr<IPlayerState> newState) {

  // 現在のステートと新しいのが同じステートだった場合
  if (state_ && typeid(*state_) == typeid(*newState)) {
    return;
  }

  state_.reset();
  state_ = std::move(newState);
  state_->SetCore(this);
  state_->Init();
  state_->Update();
}

void PlayerCore::HitFunc(std::weak_ptr<CLEYERA::Component::ObjectComponent> other) {
  // OBBの値を基にAABBの押し出し処理を計算している
  translate_ += collider_->CalcOverlapAABB(other.lock()->GetCollder());
}

void PlayerCore::Move(const Math::Vector::Vec2 &speed) {

  Math::Vector::Vec2 joyR = inputManager_->JoyLPos();

  Math::Vector::Vec2 result = joyR * speed;
  force_.x = result.x;
  force_.z = result.y;

  if (inputManager_->PushBotton(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
    force_.x *= 0.05f;
    force_.z *= 0.05f;
  }
}

void PlayerCore::Rotate() {

  Math::Vector::Vec2 rot{};
  rot.y = std::atan2(velocity_.x, velocity_.z);
  rotate_.y = rot.y;
}
