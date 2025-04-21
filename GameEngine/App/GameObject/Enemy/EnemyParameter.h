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
   // 体力
   int32_t hp_ = 0;

   // スキルの名前
   std::string skillName;
};
