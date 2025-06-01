#pragma once

#include "../../Interface/IMagicAttack.h"
#include "CLEYERA.h"

/* ベーシック攻撃 : Demo */
class PlayerAttackDemoBasic : public IMagicAttack {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerAttackDemoBasic(PlayerCore* corePtr, PlayerBulletManager* projManagerPtr);

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerAttackDemoBasic() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

  /// <summary>
  /// リセット
  /// </summary>
  void Reset() override;

  /// <summary>
  /// 攻撃処理
  /// </summary>
  void IsAttack() override;


private:

};
