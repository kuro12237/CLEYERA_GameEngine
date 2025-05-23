#pragma once

#include "CLEYERA.h" 
#include "Lua/Script/LuaScript.h"


// 前方宣言
class PlayerCore;
class InputManager;
class IPlayerCommand;

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
  /// コンストラクタ
  /// </summary>
  IMagicAttack() { name_ = "default"; }

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~IMagicAttack() = default;

  /// <summary>
  ///  攻撃処理 : 純粋仮想関数
  /// </summary>
  virtual void IsAttack() = 0;

  /// <summary>
  /// 更新処理
  /// </summary>
  virtual void Update() {};

  /// <summary>
  /// 攻撃のリセット
  /// </summary>
  virtual void Reset() {};

  /// <summary>
  /// データの読み込み
  /// </summary>
  virtual void LoadParameters(std::weak_ptr<LuaScript> lua_) = 0;


#pragma region Accessor

  // 親の設定
  void SetOwner(std::weak_ptr<PlayerCore> ptr) { owner_ = ptr; }

  // 技の名前の取得
  virtual std::string GetName() { return name_; }

#pragma endregion


protected:

  // 技名
  std::string name_ = "default";

  // 親
  std::weak_ptr<PlayerCore> owner_;

  // ダメージ
  float damage_ = 0.0f;

  // クールダウン
  float coolDown_ = 0.0f;
};
