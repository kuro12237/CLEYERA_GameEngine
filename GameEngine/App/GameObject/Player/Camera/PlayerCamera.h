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

	// ターゲットの設定
	void SetTarget(const Math::Vector::Vec3 & target) { target_ = &target; };

	// 前方ベクトルの取得
	Math::Vector::Vec3 GetForwardVec() const { return forwardVec_; }
	// 右方ベクトルの取得
	Math::Vector::Vec3 GetRightVec() const { return rightVec_; }

#pragma endregion


private:

	/// <summary>
	/// 前方&右方のベクトルを求める
	/// </summary>
	void CalcForwardAndRightVec();

	/// <summary>
	/// Vector3にアフィン変換と透視補正を適用する
	/// </summary>
	Math::Vector::Vec3 TransformWithPerspective(const Math::Vector::Vec3 & v, const Math::Matrix::Mat4x4 & m);

	/// <summary>
	/// Luaからカメラのデータをロードする
	/// </summary>
	void LoadCameraDataFromLua();

	/// <summary>
	/// Imgui関連
	/// </summary>
	void ImGuiFunc();


private:

	// カメラのLua
	std::unique_ptr<LuaScript> lua_;

	// ターゲット
	const Math::Vector::Vec3 * target_ = nullptr;

	// オフセット
	Math::Vector::Vec3 offset_{};

	// 前方&右方ベクトル
	Math::Vector::Vec3 forwardVec_{};
	Math::Vector::Vec3 rightVec_{};
};
