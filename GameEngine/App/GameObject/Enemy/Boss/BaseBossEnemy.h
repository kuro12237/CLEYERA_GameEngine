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
private:

	/// <summary>
	/// ボスの持っているスキルなど
	/// </summary>
	struct Status {

		//スキルの名前
		std::string skillName;
	};


	//ステータス
	Status status_ = {};


};
