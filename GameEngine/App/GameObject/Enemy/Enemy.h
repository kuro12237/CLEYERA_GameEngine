#pragma once

/**
 * @file Enemy.h
 * @brief 敵クラス
 * @author 茂木翼
 */


#include "BaseEnemy.h"

/// <summary>
/// 通常の敵
/// </summary>
class Enemy : public BaseEnemy {
public:
	void Init() override;

  void Update() override;

private:


};
