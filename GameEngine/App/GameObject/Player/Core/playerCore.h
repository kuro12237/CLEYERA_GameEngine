#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "Health/PlayerHealth.h"
#include "Move/PlayerMoveFunc.h"

#include "../Attack/Basic/DemoBasic/PlayerAttackDemoBasic.h"
#include "../Attack/Interface/IMagicAttack.h"
#include "../Attack/Signature/DemoSignature/PlayerAttackDemoSignature.h"
#include "../Attack/Standard/DemoStandard/PlayerAttackDemoStandard.h"
#include "../Bullet/Manager/PlayerBulletManager.h"

// 前方宣言
class PlayerCamera;

/* Playerの実体クラス */
class PlayerCore : public CLEYERA::Component::ObjectComponent {

public:
  /// <summary>
  /// コンストラク
  /// </summary>
  PlayerCore();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerCore() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

  /// <summary>
  /// Padの移動処理
  /// </summary>
  void PadMove();

  /// <summary>
  /// Keyの移動処理
  /// </summary>
  void KeyMove(const Math::Vector::Vec2 &input);

  /// <summary>
  /// ベーシック攻撃
  /// </summary>
  void BasicAttack();

  /// <summary>
  /// スタンダード攻撃
  /// </summary>
  void StandardAttack();

  /// <summary>
  /// シグネチャー攻撃
  /// </summary>
  void SignatureAttack();

  /// <summary>
  /// 衝突時コールバック
  /// </summary>
  void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Accessor

  // ワールド座標の取得
  inline Math::Vector::Vec3 GetWorldPos() const {
    return ObjectComponent::gameObject_->GetWorldPos();
  }

  // カメラのweak_ptrの設定
  inline void SetCameraPtr(std::weak_ptr<PlayerCamera> camera) {
    weakpCamera_ = camera;
    moveFunc_->SetCameraPtr(camera);
  }

  // プレイヤーの向いている方向
  inline Math::Vector::Vec3 GetDirection() {
    return {
        std::sinf(rotate_.y),
        0.0f,
        std::cosf(rotate_.y),
    };
  }

  /// <summary>
  /// hp計算関数をセット
  /// </summary>
  void SetHpCalcfunc(std::function<void(int32_t)> hpCalcFunc) { hpCalcFunc_ = hpCalcFunc; };

#pragma endregion

private:
  /// <summary>
  /// 攻撃スロットの初期化
  /// </summary>
  void InitAttackSlot();

  /// <summary>
  /// Luaからデータを抽出する
  /// </summary>
  void LoadCoreDataFromLua();

  /// <summary>
  /// ノックバック
  /// </summary>
  void KnockBack();

private:
  /// <summary>
  /// hp計算関数ポインタ
  /// </summary>
  /// <param name="power"></param>
  /// <returns></returns>
  std::function<void(int32_t)> hpCalcFunc_;
  // ノックバックの距離
  const float_t KNOCK_BACK_DISTANCE_ = 5.0f;
  // 時間変化
  const float_t DELTA_TIME_ = 1.0f / 60.0f;
  // 線形補間
  const float_t INCREASE_T_VALUE_ = 0.1f;
  // 最大ノックバック時間
  const float_t MAX_KNOCK_BACK_TIME_ = 3.0f;

private:
  // Cameraのweak_ptr
  std::weak_ptr<PlayerCamera> weakpCamera_;

  // PlayerCoreのLua
  std::unique_ptr<LuaScript> lua_;

  // 体力
  std::unique_ptr<PlayerHealth> health_;
  // 移動処理
  std::unique_ptr<PlayerMoveFunc> moveFunc_;

  // 攻撃コマンド
  std::array<std::unique_ptr<IMagicAttack>, 3> attacks_;

  // 弾管理クラス
  std::unique_ptr<PlayerBulletManager> bulletManager_;

  // ノックバック
  bool isKnockBack_ = false;
  // 時間
  float_t knockBackTime_ = 0.0f;
  // 線形補間
  float_t knockbackT_ = 0.0f;
  // 方向を決める
  bool isDesidePosition_ = false;

  // ノックバック前の座標
  Math::Vector::Vec3 beforeKnockBackPosition_ = {};
  // ノックバック後の座標
  Math::Vector::Vec3 afterKnockBackPosition_ = {};
};