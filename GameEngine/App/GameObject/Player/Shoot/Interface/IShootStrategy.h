#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 射撃のタイプ
enum class ShootCommandType {
  None = -1,
  Basic = 0,
  Standard = 1,
  Signature = 2,

};

/* 射撃方法の基底クラス */
class IShootStrategy {

public:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  IShootStrategy() = default;

  /// <summary>
  /// デストラクタ
  /// </summary>
  virtual ~IShootStrategy() = default;

  /// <summary>
  /// 初期化処理
  /// </summary>
  virtual void Init() = 0;

  /// <summary>
  /// 更新処理
  /// </summary>
  virtual void Update() = 0;

  /// <summary>
  /// 射撃処理の純粋仮想関数
  /// </summary>
  virtual void Shoot() = 0;

#pragma region

  // タイプの取得
  inline ShootCommandType GetShootCommandType() const { return type_; }

#pragma endregion


protected:

    // 射撃タイプ
    ShootCommandType type_ = ShootCommandType::None;
};
