#include "playerCore.h"
#include "../Camera/PlayerCamera.h"
#include "Wall/Wall.h"

/// <summary>
/// コンストラク
/// </summary>
PlayerCore::PlayerCore() {
  lua_ = std::make_unique<LuaScript>();
  moveFunc_ = std::make_unique<PlayerMoveFunc>(this);
  projManager_ = std::make_unique<PlayerProjectileManager>();
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerCore::Init() {
  // クラス名
  ObjectComponent::name_ = VAR_NAME(PlayerCore);

  // Luaの読み込み
  lua_->LoadScript("Player/Core", "PlayerCore");
  lua_->SetReloadCallBack([this]() { LoadCoreDataFromLua(); });

  // Luaから抽出したデータの設定
  LoadCoreDataFromLua();

  // Modelの設定
  std::pair<std::string, std::string> str = {"Resources/Model/Player/Core", "Core"};
  uint32_t handle = ObjectComponent::modelManager_->LoadModel(str.first, str.second);
  ObjectComponent::gameObject_->ChangeModel(handle);

  // コライダー作成
  ObjectComponent::CreateCollider(ColliderType::AABB);

  // 移動処理クラスの初期化
  moveFunc_->Init();

  // 初期攻撃スロット
  attacks_[ToIndex(AttackType::Basic)] =
      std::make_unique<PlayerAttackDemoBasic>(this, projManager_.get());

  // あたりはんてい関数セット
  collider_->SetHitCallFunc(
      [this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerCore::Update() {
  TransformUpdate();

  // 移動処理クラス
  moveFunc_->Update();

  // 発射物管理クラス
  projManager_->Update();


  //ノックバック
  KnockBack();

#ifdef _DEBUG
  ImGui::Begin("PlayerCore");
  ImGui::Checkbox("IsKockBack", &isKnockBack_);
  ImGui::End();

  projManager_->DrawImGui();
#endif // _DEBUG
}

/// <summary>
/// Padの移動処理
/// </summary>
void PlayerCore::PadMove() { moveFunc_->PadMove(); }

/// <summary>
/// Keyの移動処理
/// </summary>
void PlayerCore::KeyMove(const Math::Vector::Vec2 &input) { moveFunc_->KeyMove(input); }

/// <summary>
/// ベーシック攻撃
/// </summary>
void PlayerCore::BasicAttack() { attacks_[ToIndex(AttackType::Basic)]->IsAttack(); }

/// <summary>
/// スタンダード攻撃
/// </summary>
void PlayerCore::StandardAttack() { attacks_[ToIndex(AttackType::Standard)]->IsAttack(); }

/// <summary>
/// シグネチャー攻撃
/// </summary>
void PlayerCore::SignatureAttack() { attacks_[ToIndex(AttackType::Signature)]->IsAttack(); }

void PlayerCore::OnCollision([[maybe_unused]] std::weak_ptr<ObjectComponent> other) {

  if (auto obj = other.lock()) {
    // Wall 型にキャストできるかをチェック
    if (auto wall = std::dynamic_pointer_cast<Wall>(obj)) {
      // Wall にぶつかったときの処理
      auto aabb = std::dynamic_pointer_cast<CLEYERA::Util::Collider::AABBCollider>(
          wall->GetCollder().lock());
      // 押し出し
      this->translate_ -= aabb->GetAABB().push;
    }
  }
}

/// <summary>
/// Luaからデータを抽出する
/// </summary>
void PlayerCore::LoadCoreDataFromLua() {
  translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}

void PlayerCore::KnockBack() {
  // ランダムの値で位置を決める
  // SRは固定
  std::uniform_real_distribution<float_t> distribute(-1.0f, 1.0f);
  // ランダムエンジン
  std::random_device seedGenerator;
  std::mt19937 randomEngine(seedGenerator());
  if (isKnockBack_ == true) {
    Math::Vector::Vec3 knockBackDirection = {};
    if (isDesidePosition_ == false) {
      knockBackDirection = {
          .x = distribute(randomEngine), .y = 0.0f, .z = distribute(randomEngine)};
      beforeKnockBackPosition_ = translate_;
      afterKnockBackPosition_ =
          beforeKnockBackPosition_ + knockBackDirection * KNOCK_BACK_DISTANCE_;
      isDesidePosition_ = true;
    }

    // ノックバックの時間
    knockBackTime_ += DELTA_TIME_;
    // 線形補間
    knockbackT_ += INCREASE_T_VALUE_;
    // 座標を線形補間でやるよ！
    translate_ =
        Math::Vector::Func::Lerp(beforeKnockBackPosition_, afterKnockBackPosition_, knockbackT_);
    knockbackT_ = std::clamp(knockbackT_, 0.0f, 1.0f);

    // 制限を超えたら0に戻る
    if (knockbackT_ >= 1.0f ) {
      beforeKnockBackPosition_ = {};
      afterKnockBackPosition_ = {};

      knockBackTime_ = 0.0f;
      knockbackT_ = 0.0f;
      isKnockBack_ = false;
      isDesidePosition_ = false;
    }
  }
}
