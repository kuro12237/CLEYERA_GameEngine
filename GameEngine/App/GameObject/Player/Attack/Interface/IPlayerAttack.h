#pragma once

#include "CLEYERA.h"

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
  ~IPlayerAttack() = default;

  /// <summary>
  ///  攻撃処理 : 純粋仮想関数
  /// </summary>
  virtual void Attack() = 0;

  /// <summary>
  /// 技の名前の取得
  /// </summary>
  virtual std::string GetName() { return name_; }

private:

  // 技名
  std::string name_ = "default";

};
