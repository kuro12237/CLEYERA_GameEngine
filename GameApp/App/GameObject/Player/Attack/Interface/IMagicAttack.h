#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 前方宣言
class PlayerCore;
class InputManager;
class IPlayerCommand;
class PlayerBulletManager;
class EnemyManager;

// 攻撃のタイプ
enum class AttackType {
  None = -1,
  Low,
  High,
  Special,
};
inline size_t ToIndex(AttackType type) { return static_cast<size_t>(type); }

/* プレイヤー攻撃の基底クラス */
class IMagicAttack {

public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~IMagicAttack() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  virtual void Init() {};

  /// <summary>
  /// 更新処理
  /// </summary>
  virtual void Update() {};

  /// <summary>
  /// 攻撃のリセット
  /// </summary>
  virtual void Reset() {};

  /// <summary>
  ///  攻撃処理 : 純粋仮想関数
  /// </summary>
  virtual void IsAttack() = 0;

  /// <summary>
  /// Ptrの設定
  /// </summary>
  void SetPre(PlayerCore *corePtr, std::weak_ptr<PlayerBulletManager> bulManPtr, std::weak_ptr<EnemyManager> eneManPtr) {
    owner_ = corePtr;
    bulletManager_ = bulManPtr;
    enemyMgr_ = eneManPtr;
  }

  /// <summary>
  /// クールダウン開始
  /// </summary>
  void SetAttackCoolDown();

  /// <summary>
  /// クールダウンタイマーの更新
  /// </summary>
  void UpdateCoolDownTimer();

  /// <summary>
  /// ImGuiの描画
  /// </summary>
  virtual void DrwaImGui() {};

#pragma region Accessor

  // 親の設定
  void SetOwner(PlayerCore *ptr) { owner_ = ptr; }

  // 技の名前の取得
  virtual std::string GetName() { return name_; }

  // 攻撃中
  virtual bool IsAttacking() const { return isAttacking_; }

  // クールダウン中
  virtual bool IsCoolDown() const { return isAttackCoolDown_; }

#pragma endregion

protected:
  /// <summary>
  /// 速度を求める
  /// </summary>
  Math::Vector::Vec3 CalcVelocity(const Math::Vector::Vec3 &vel);

protected:
  // 技名
  std::string name_ = "default";

  // 親
  PlayerCore *owner_ = nullptr;

  // バレット管理クラスのweakPtr
  std::weak_ptr<PlayerBulletManager> bulletManager_;

  // エネミーマネージャー
  std::weak_ptr<EnemyManager> enemyMgr_;

  // ダメージ
  float damage_ = 0.0f;

  // クールダウン
  bool isAttackCoolDown_ = false;
  float coolDownTimer_ = 0.0f;
  float coolDownInterval_ = 0.0f;

  // 攻撃中
  bool isAttacking_ = false;
  
  // 弾の個数
  size_t bulletCount_ = 0;
};
