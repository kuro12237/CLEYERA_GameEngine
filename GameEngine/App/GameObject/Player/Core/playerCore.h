#pragma once

#include "CLEYERA.h"


/* Playerの実体クラス */
class PlayerCore : public CLEYERA::Component::ObjectComponent {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCore() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCore() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;



#pragma region Accessor

	// ワールド座標の取得
	inline Math::Vector::Vec3 GetWorldPos() const {
		return ObjectComponent::gameObject_->GetWorldPos();
	}

#pragma endregion


};