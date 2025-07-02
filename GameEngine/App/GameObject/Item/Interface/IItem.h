#pragma once

#include "CLEYERA.h"


/* Item系の基底クラス */
class IItem : public CLEYERA::Component::ObjectComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IItem() = default;
	
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IItem() = default;

};
