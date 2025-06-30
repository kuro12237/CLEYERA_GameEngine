#pragma once

#include "../../../Bullet/DemoSignature/PlayerDemoSignatureBullet.h"
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
  /// <summary>
  /// 指定した軸の周りにベクトルを回転させます。
  /// </summary>
  Math::Vector::Vec3 RotateAroundAxis(const Math::Vector::Vec3 &v, const Math::Vector::Vec3 &axis,
                                      float angle);

private:
  int directionCount_ = 5; // デフォルトは8方向
};