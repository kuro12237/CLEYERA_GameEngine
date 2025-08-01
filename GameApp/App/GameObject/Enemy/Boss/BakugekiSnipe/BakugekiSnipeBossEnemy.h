#pragma once

/**
 * @file BakugekiSnipeBossEnemy.h
 * @brief 最初の敵クラス
 * @author 茂木翼
 */

#include "Enemy/Boss/BaseBossEnemy.h"


/// <summary>
/// 最初の敵
/// </summary>
class BakugekiSnipeBossEnemy : public BaseBossEnemy {
 public:
	/// <summary>
   /// 最初のボス
   /// </summary>
   BakugekiSnipeBossEnemy() = default;

   /// <summary>
   /// 初期化
   /// </summary>
   void Init() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

   /// <summary>
   /// ImGui更新
   /// </summary>
   void ImGuiUpdate() override;

   /// <summary>
   /// ノックバック
   /// </summary>
   void KnockBack();

   /// <summary>
   /// 倒された
   /// </summary>
   void Killed();


   /// <summary>
   /// デストラクタ
   /// </summary>
   ~BakugekiSnipeBossEnemy() override = default;

   void OnCollision(std::weak_ptr<ObjectComponent> other);


};
