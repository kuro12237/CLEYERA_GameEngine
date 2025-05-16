#pragma once

/**
 * @file EnemyParameter.h
 * @brief 敵のパラメーター
 * @author 茂木翼
 */

#include <cstdint>
#include <string>

/// <summary>
/// 敵のパラメーター
/// </summary>
struct EnemyParameter {
	//最大の体力
	int32_t maxHp_ = 0;

   // 体力
   int32_t hp_ = 0;

   // スキルの名前
   std::string skillName;

   //ノックバック変数
   float_t knockBackDistance_ = 0.0f;

};
