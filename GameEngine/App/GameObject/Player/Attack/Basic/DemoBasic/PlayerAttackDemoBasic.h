#pragma once

#include "CLEYERA.h"
#include "../../Interface/IPlayerAttack.h"


/* ベーシック攻撃 : Demo */
class PlayerAttackDemoBasic : public IPlayerAttack {

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


private:


};
