#pragma once

#include "CLEYERA.h"

// 前方宣言
class PlayerCore;

// 攻撃のタイプ
enum class AttackType {
	None = -1,
	Basic,
	Standard,
	Signature,
};
inline size_t ToIndex(AttackType type) { return static_cast<size_t>(type); }


/* プレイヤー攻撃の基底クラス */
class IPlayerAttack {

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  IPlayerAttack() { name_ = "default"; }

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~IPlayerAttack() = default;

  /// <summary>
  ///  攻撃処理 : 純粋仮想関数
  /// </summary>
  virtual void IsAttack() = 0;

  /// <summary>
  /// 技の名前の取得
  /// </summary>
  virtual std::string GetName() { return name_; }


#pragma region

  // 親の設定
  void SetOwner(std::weak_ptr<PlayerCore> ptr) { owner_ = ptr; }

#pragma endregion


private:

  // 技名
  std::string name_ = "default";

  // 親
  std::weak_ptr<PlayerCore> owner_;
};
