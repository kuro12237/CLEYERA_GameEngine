#pragma once

#include "CLEYERA.h"


/* Item系の基底クラス */
class IItem : public CLEYERA::Component::ObjectComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IItem() {};
	
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IItem() {};

#pragma region 

	// 座標
	void SetPostion(const Math::Vector::Vec3 & pos) { translate_ = pos; }

#pragma endregion 

};
