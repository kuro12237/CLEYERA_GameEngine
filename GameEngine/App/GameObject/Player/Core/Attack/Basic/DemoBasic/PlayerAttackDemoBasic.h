#pragma once

#include "../../Interface/IMagicAttack.h"
#include "CLEYERA.h"

/* ベーシック攻撃 : Demo */
class PlayerAttackDemoBasic : public IMagicAttack {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerAttackDemoBasic();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerAttackDemoBasic() = default;

  /// <summary>
  /// 攻撃処理
  /// </summary>
  void IsAttack() override;

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

  /// <summary>
  /// リセット
  /// </summary>
  void Reset() override;

  /// <summary>
  /// データの読み込み
  /// </summary>
  void LoadParameters(std::weak_ptr<LuaScript> lua_) override;



private:

};
