#pragma once

/**
 * @file BaseNormalEnemy.h
 * @brief 雑魚敵の基底クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"
#include "Enemy/EnemyParameter.h"
#include "Enemy/Normal/Behavior/NormalEnemyBehaviorNode.h"

/// <summary>
/// 雑魚敵の基底クラス
/// </summary>
class BaseNormalEnemy : public CLEYERA::Component::ObjectComponent {
public:
   /// <summary>
   /// プレイヤーの座標
   /// </summary>
   /// <param name="position">座標</param>
   inline void SetPlayerPosition(const Math::Vector::Vec3 &position) { 
	   this->playerPosition_ = position; 
   }

   /// <summary>
   /// 生成時の初期座標
   /// </summary>
   /// <param name="position">座標</param>
   inline void SetInitialPosition(const Math::Vector::Vec3 &position) { 
	   this->translate_ = position; 
   }
   /// <summary>
   /// ベロシティの設定
   /// </summary>
   /// <param name="velocity">ベロシティ</param>
   inline void SetVelocity(const Math::Vector::Vec3 & velocity) {
	   this->velocity_ = velocity;
	}

   /// <summary>
   /// 座標の取得
   /// </summary>
   /// <returns>座標</returns>
   inline Math::Vector::Vec3 GetPosition()const {
	   return translate_;
   }

   /// <summary>
   /// プレイヤーの座標を取得
   /// </summary>
   /// <returns>座標</returns>
   inline Math::Vector::Vec3 GetPlayerPosition()const {
	   return playerPosition_;
   }

   /// <summary>
   /// パラメーターを取得
   /// </summary>
   /// <returns></returns>
   inline EnemyParameter GetBossEnemyParameter()const {
	   return parameter_;
   }

protected:
	// プレイヤー座標
	Math::Vector::Vec3 playerPosition_ = {};
	//パラメーター
    EnemyParameter parameter_ = {};
	//方向
    Math::Vector::Vec3 direction_ = {};
	//ビヘイビアツリー
	std::unique_ptr<NormalEnemyBehaviorNode> behaviorTree_ = nullptr;


	
};
