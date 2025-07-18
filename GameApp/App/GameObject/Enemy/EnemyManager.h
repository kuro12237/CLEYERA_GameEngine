#pragma once

/**
 * @file EnemyManager.h
 * @brief 敵管理クラス
 * @author 茂木翼
 */

#include <list>

#include "Boss/BaseBossEnemy.h"
#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"
#include "Normal/BaseNormalEnemy.h"

/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager;

/// <summary>
/// 敵管理クラス
/// </summary>
class EnemyManager : public CLEYERA::Component::ManagerComponent {
public:
  /// <summary>
  /// 初期化
  /// </summary>
  void Init() override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update() override;

  /// <summary>
  /// 雑魚敵を生成
  /// </summary>
  /// <param name="position">座標</param>
  void GenerateNormalEnemy1(const Math::Vector::Vec3 &position,std::string name ="");

  /// <summary>
  /// 雑魚敵2を生成
  /// </summary>
  /// <param name="position">座標</param>
  void GenerateNormalEnemy2(const Math::Vector::Vec3 &position, std::string name = "");

  /// <summary>
  /// 雑魚敵3を生成
  /// </summary>
  /// <param name="position"></param>
  /// <param name="name"></param>
  void GenerateNormalEnemy3(const Math::Vector::Vec3 &position, std::string name = "");

  /// <summary>
  /// ボス敵
  /// </summary>
  /// <param name="position">座標</param>
  void GenerateBossEnemyEnemy(const Math::Vector::Vec3 &position);

  /// <summary>
  /// ImGui
  /// </summary>
  void ImGuiUpdate() override;

private:
  /// <summary>
  /// Luaの読み込み
  /// </summary>
  void LoadEnemy2DataFromLua();

public:
  /// <summary>
  /// プレイヤー管理クラスの設定
  /// </summary>
  /// <param name="playerManager">プレイヤー管理クラス</param>
  inline void SetPlayerManager(PlayerManager *playerManager) {
    this->playerManager_ = playerManager;
  }

  /// <summary>
  /// 敵が存在しているかどうか
  /// </summary>
  /// <returns></returns>
  inline bool GetIsExist() const {
    // 雑魚敵の数を調べる
    if (enemyList_.size() != 0u) {
      return true;
    }
    // ボス敵の数を調べる
    if (bossEnemyList_.size() != 0u) {
      return true;
    }
    return false;
  }
  const size_t &GetEnemyCount() const { return enemyCount_; }

private:
  size_t enemyCount_ = 0;

  // プレイヤー管理クラス
  PlayerManager *playerManager_ = nullptr;
  // 座標
  Math::Vector::Vec3 playerPosition_ = {};

  // 雑魚敵
  std::list<std::weak_ptr<BaseNormalEnemy>> enemyList_;

  // PlayerCoreのLua
  std::unique_ptr<LuaScript> lua_;

  // ボス敵
  std::list<std::weak_ptr<BaseBossEnemy>> bossEnemyList_;

  // 生成の文字列を入れる
  std::stringstream enemyPositionsFromCSV_;
};
