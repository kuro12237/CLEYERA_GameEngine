#pragma once

/**
 * @file BaseNormalEnemy.h
 * @brief 敵の基底クラス
 * @author 茂木翼
 */

#include"CLEYERA.h"
#include "State/BaseNormalEnemyState.h"

/// <summary>
/// 敵の基底クラス
/// </summary>
class BaseNormalEnemy : public CLEYERA::Component::ObjectComponent {


public:
   /// <summary>
   /// 状態遷移
   /// </summary>
   /// <param name="newState">新しい状態</param>
   void ChangeState(std::unique_ptr<BaseNormalEnemyState> newState);

protected:

	//状態
	std::unique_ptr<BaseNormalEnemyState> currentState_ = nullptr;

};