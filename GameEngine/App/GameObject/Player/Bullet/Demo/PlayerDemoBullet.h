#pragma once

#include "../Interface/IPlayerBullet.h"

struct PlayerDemoBulletParam {
  float horizontalCurve = 0.0f; // 左右カーブ強さ（右:正 / 左:負）
  float verticalCurve = 0.0f;   // 上下カーブ強さ（上:正 / 下:負）
  float curveDistance = 10.0f;  // カーブ終了までのZ軸距離（始点から）
  bool useDistance = true;      // 距離ベースで終点判定するか
  float curveTime = 1.0f;       // 時間ベースで終了する場合の秒数
  enum class CurveType {
    None,
    SinWave,
    Linear,
    EaseInOut,
  } type = CurveType::SinWave;
};

class PlayerDemoBullet : public IPlayerBullet {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  PlayerDemoBullet();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~PlayerDemoBullet() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update() override;

  /// <summary>
  /// パラメーターの設定
  /// </summary>
  void SetParam(const PlayerDemoBulletParam &param) { param_ = param; }

private:
  /// <summary>
  /// 移動処理
  /// </summary>
  void Move();

private:
  Math::Vector::Vec3 initVel_ = {0, 0, 1}; // 弾の初期速度
  PlayerDemoBulletParam param_;            // カーブ情報
  float traveledDistance_ = 0.0f;          // Z軸方向に進んだ距離
  float elapsedTime_ = 0.0f;               // 経過時間
};