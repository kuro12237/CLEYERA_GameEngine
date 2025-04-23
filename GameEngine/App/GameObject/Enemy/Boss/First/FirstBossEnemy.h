#pragma once

/**
 * @file FirstBossEnemy.h
 * @brief 最初の敵クラス
 * @author 茂木翼
 */

#include "Enemy/Boss/BaseBossEnemy.h"
#include "Enemy/Boss/Behavior/BossEnemyBehaviorNode.h"


/// <summary>
/// 最初の敵
/// </summary>
class FirstBossEnemy : public BaseBossEnemy {
 public:
	/// <summary>
   /// 最初のボス
   /// </summary>
   FirstBossEnemy() = default;

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
   ~FirstBossEnemy() override = default;


private:
	//ビヘイビアツリー
	std::unique_ptr<BossEnemyBehaviorNode> behaviorTree_;



   
};
