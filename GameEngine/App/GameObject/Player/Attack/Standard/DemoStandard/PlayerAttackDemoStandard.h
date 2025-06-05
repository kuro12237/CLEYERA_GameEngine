#pragma once

#include "../../../Bullet/DemoStandard/PlayerDemoStandardBullet.h"
#include "../../Interface/IMagicAttack.h"
#include "CLEYERA.h"

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
  void StartAttack(); // 攻撃開始
  void FireOneBullet(int columnIndex); // 1発発射(列指定)

private:
  // 連射用制御
  int shotIndex_ = 0;         // 発射した弾のインデックス(0〜5)
  int shotsPerSequence_ = 6;  // 合計発射数
  int shotsPerRow_ = 3;       // 1列あたりの弾数（右・中・左）
  float shotInterval_ = 5.0f; // 発射間隔（フレーム数）
  float shotTimer_ = 0.0f;    // 発射タイマー

  bool isShooting_ = false; // 攻撃開始フラグ
};