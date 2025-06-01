#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 前方宣言
class PlayerCore;
class InputManager;
class IPlayerCommand;
class PlayerBulletManager;

// 攻撃のタイプ
enum class AttackType {
  None = -1,
  Basic,
  Standard,
  Signature,
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
  void SetPre(PlayerCore* corePtr, PlayerBulletManager* projManagerPtr)
  {
    owner_ = corePtr;
    projManager_ = projManagerPtr;
  }

#pragma region Accessor

  // 親の設定
  void SetOwner(PlayerCore* ptr) { owner_ = ptr; }

  // ProjectileManagerの設定
  void SetProjectileManager(PlayerBulletManager* ptr) { projManager_ = ptr; }

  // 技の名前の取得
  virtual std::string GetName() { return name_; }

#pragma endregion

protected:

  // 技名
  std::string name_ = "default";

  // 親
  PlayerCore *owner_ = nullptr;

  // 発射物管理クラスのweakPtr
  PlayerBulletManager *projManager_ = nullptr;

  // ダメージ
  float damage_ = 0.0f;

  // クールダウン
  float coolDown_ = 0.0f;
};
