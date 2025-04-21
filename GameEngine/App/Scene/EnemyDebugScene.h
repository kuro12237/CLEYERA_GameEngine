#pragma once

/**
 * @file EnemyDebugScene.h
 * @brief 敵のデバッグ用のクラス
 * @author 茂木翼
 */

#include "IScene.h"
#include "test/TestObject.h"
#include "test/testCamera.h"
#include "Player/PlayerManager.h"
#include "Enemy/EnemyManager.h"

/// <summary>
/// 敵のデバッグシーン
/// </summary>
class EnemyDebugScene : public SceneCompornent {
 public:
   /// <summary>
   /// コンストラクタ
   /// </summary>
   EnemyDebugScene()=default;
   
   /// <summary>
   /// 初期化
   /// </summary>
   void Init() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

   /// <summary>
   /// デストラクタ
   /// </summary>
   ~EnemyDebugScene()override=default;

 private:
	//プレイヤー管理クラス
	std::shared_ptr<PlayerManager> playerManager_ = nullptr;

	//敵管理クラス
    std::shared_ptr<EnemyManager> enemyManager_ = nullptr;


};
