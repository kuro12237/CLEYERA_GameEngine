#pragma once

/**
 * @file BaseBossEnemy.h
 * @brief ボスの基底クラス
 * @author 茂木翼
 */


#include"CLEYERA.h"

/// <summary>
/// ボスの基底クラス
/// </summary>
class BaseBossEnemy : public CLEYERA::Component::ObjectComponent {
public:
   /// <summary>
   /// プレイヤーの座標
   /// </summary>
   /// <param name="position"></param>
   inline void SetPlayerPosition(const Math::Vector::Vec3 &position) { 
	   this->playerPosition_ = position; 
   }

   /// <summary>
   /// 生成時の初期座標
   /// </summary>
   /// <param name="position"></param>
   inline void SetInitialPosition(const Math::Vector::Vec3 &position) { 
	   this->translate_ = position; 
   }

protected:

	// プレイヤー座標
	Math::Vector::Vec3 playerPosition_ = {};


	/// <summary>
	/// ボスの持っているスキルなど
	/// </summary>
	struct Status {

		//体力
        int32_t hp_ = 0;

		//スキルの名前
		std::string skillName;
	};


	//ステータス
	Status status_ = {};


	//方向
    Math::Vector::Vec3 direction_ = {};


};
