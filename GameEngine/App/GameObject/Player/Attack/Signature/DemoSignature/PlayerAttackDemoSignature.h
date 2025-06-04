#pragma once

#include "../../../Bullet/Demo/PlayerDemoBullet.h"
#include "../../Interface/IMagicAttack.h"
#include "CLEYERA.h"

/* シグネチャー攻撃 : Demo */
class PlayerAttackDemoSignature : public IMagicAttack {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerAttackDemoSignature(PlayerCore *corePtr, PlayerBulletManager *bulManagerPtr);

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerAttackDemoSignature() = default;

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