#pragma once

/**
 * @file NormalEnemy2Bullet.h
 * @brief 雑魚敵2クラス
 * @author 茂木翼
 */

//一直線

#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "NormalEnemy2Bullet.h"

/// <summary>
/// 最初の敵
/// </summary>
class NormalEnemy2 : public BaseNormalEnemy {
 public:
	/// <summary>
   /// 最初のボス
   /// </summary>
   NormalEnemy2() = default;

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
   ~NormalEnemy2() override = default;


private:
	/// <summary>
	/// ImGui表示用
	/// </summary>
	void DisplayImGui();

private:
	//攻撃中かどうか
	bool isAttacking_ = false;

	// 弾のリスト
    std::list<std::shared_ptr<NormalEnemy2Bullet>> bullets_;

	
};
