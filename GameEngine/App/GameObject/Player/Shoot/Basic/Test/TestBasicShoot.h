#pragma once

#include "../../Interface/IShootStrategy.h"


/* テスト用のベーシック攻撃クラス */
class TestBasicShoot : public IShootStrategy {

public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TestBasicShoot();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TestBasicShoot() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Shoot() override;

private:



};