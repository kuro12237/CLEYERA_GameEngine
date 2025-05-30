#pragma once

/**
 * @file NormalEnemy1.h
 * @brief 雑魚敵1クラス
 * @author 茂木翼
 */

//詳しい挙動とかはここにあるよ
//https://docs.google.com/presentation/d/1LTi0n_xoAkvzk13g5KMXGNqeEhtBJlnYJjtetUjhM7M/edit#slide=id.p

#include <list>

#include "Enemy/Normal/BaseNormalEnemy.h"
#include "NormalEnemy1Bullet.h"

/// <summary>
/// 最初の敵
/// </summary>
class NormalEnemy1 : public BaseNormalEnemy {
 public:
	/// <summary>
   /// 最初のボス
   /// </summary>
	 NormalEnemy1() = default;

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
   ~NormalEnemy1() override = default;


private:
	/// <summary>
	/// ImGui表示用
	/// </summary>
	void DisplayImGui();

private:

    bool isAttack_ = false;

};
