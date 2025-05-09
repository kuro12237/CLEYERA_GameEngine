#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"


class PlayerCamera : public CLEYERA::Component::CameraCompornent {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCamera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCamera() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;


#pragma region Accessor

	void SetTarget(const Math::Vector::Vec3 & target) { target_ = &target; };

#pragma endregion


private:

	/// <summary>
	/// Luaからカメラのデータをロードする
	/// </summary>
	void LoadCameraDataFromLua();

	/// <summary>
	/// Imgui関連
	/// </summary>
	void ImGuiFunc();


private:

	const Math::Vector::Vec3 * target_ = nullptr;
	Math::Vector::Vec3 offset_{};

	std::unique_ptr<LuaScript> lua_;
};
