#pragma once

/**
 * @file FirstBossEnemy.h
 * @brief 最初の敵クラス
 * @author 茂木翼
 */

#include "Enemy/Boss/BaseBossEnemy.h"


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
   /// ImGui更新
   /// </summary>
   void ImGuiUpdate() override;

   /// <summary>
   /// 当たり判定
   /// </summary>
   /// <param name="other"></param>
   void OnCollision(std::weak_ptr<ObjectComponent> other);

   /// <summary>
   /// デストラクタ
   /// </summary>
   ~FirstBossEnemy() override = default;

private:
   /// <summary>
   /// ノックバック
   /// </summary>
   void KnockBack() override;

   /// <summary>
   /// 倒された
   /// </summary>
   void Killed() override;
   
};
