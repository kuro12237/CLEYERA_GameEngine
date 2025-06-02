#pragma once

#include "../Interface/IPlayerBullet.h"

class PlayerDemoBullet : public IPlayerBullet {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerDemoBullet();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerDemoBullet() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;


	private:

		/// <summary>
		/// 移動処理
		/// </summary>
		void Move();


};