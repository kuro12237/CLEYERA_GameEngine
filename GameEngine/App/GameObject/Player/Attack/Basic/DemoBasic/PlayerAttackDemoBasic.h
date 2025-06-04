#pragma once

#include "../../../Bullet/Demo/PlayerDemoBullet.h"
#include "../../Interface/IMagicAttack.h"
#include "CLEYERA.h"

/* ベーシック攻撃 : Demo */
class PlayerAttackDemoBasic : public IMagicAttack {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerAttackDemoBasic(PlayerCore *corePtr, PlayerBulletManager *bulManagerPtr);

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
  /// <summary>
  /// Bulletを生成
  /// </summary>
  void FireBullet();

  /// <summary>
  /// パラメーターの取得
  /// </summary>
  PlayerDemoBulletParam GetBulletParam();

private:
  // コンボの段階
  int comboStep_ = 0;
  // コンボのMax
  const int maxCombo_ = 3;
  // コンボのタイマー
  float comboTimer_ = 0.0f;
  // コンボインターバル
  float comboInterval_ = 0.0f;

  // Luaスクリプト
  std::unique_ptr<LuaScript> lua_;
};
