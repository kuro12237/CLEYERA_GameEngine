#pragma once

#include "CLEYERA.h"
#include "../../../Bullet/Demo/PlayerDemoBullet.h"
#include "../../Interface/IMagicAttack.h"

/* スタンダード攻撃 : Demo */
class PlayerAttackDemoStandard : public IMagicAttack {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerAttackDemoStandard(PlayerCore *corePtr, PlayerBulletManager *bulManagerPtr);

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerAttackDemoStandard() = default;

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