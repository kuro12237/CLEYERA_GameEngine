#include "PlayerCamera.h"



/// <summary>
/// コンストラク
/// </summary>
PlayerCamera::PlayerCamera()
{
	lua_ = std::make_unique<LuaScript>();
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerCamera::Init()
{
	name_ = VAR_NAME(PlayerCamera);

	// Luaの読み込み
	lua_->LoadScript("LuaScript/Player/Camera", "PlayerCamera.lua");
	lua_->SetReloadCallBack([this]() {LoadCameraDataFromLua(); });

	// Luaから抽出したデータの設定
	LoadCameraDataFromLua();


	CameraChange();
	this->SetImGuiFunc(std::bind(&PlayerCamera::ImGuiFunc, this));
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerCamera::Update()
{
	translate_ = *target_ + offset_;

	// 前方&右方のベクトルを求める
	CalcForwardAndRightVec();
}


/// <summary>
/// 前方&右方のベクトルを求める
/// </summary>
void PlayerCamera::CalcForwardAndRightVec()
{
	// 前方ベクトルのデフォルト値
	Math::Vector::Vec3 defForwardVec = Math::Vector::Vec3{ 0.0f, 0.0f, 1.0f };
	// 右方ベクトルのデフォルト値
	Math::Vector::Vec3 defRightVec = Math::Vector::Vec3{ 1.0f, 0.0f, 0.0f };

	// Y軸の回転行列
	Math::Matrix::Mat4x4 rotateYMat = Math::Matrix::Func::RotateYMatrix(rotate_.y);

	// 前方ベクトルを求める
	forwardVec_ = TransformWithPerspective(defForwardVec, rotateYMat);
	// 右方ベクトルを求める
	rightVec_ = TransformWithPerspective(defRightVec, rotateYMat);
}


/// <summary>
/// Vector3にアフィン変換と透視補正を適用する
/// </summary>
Math::Vector::Vec3 PlayerCamera::TransformWithPerspective(const Math::Vector::Vec3 & v, const Math::Matrix::Mat4x4 & m)
{
	Math::Vector::Vec3 result = {
		(v.x * m.m[ 0 ][ 0 ]) + (v.y * m.m[ 1 ][ 0 ]) + (v.z * m.m[ 2 ][ 0 ]) + (1.0f * m.m[ 3 ][ 0 ]),
		(v.x * m.m[ 0 ][ 1 ]) + (v.y * m.m[ 1 ][ 1 ]) + (v.z * m.m[ 2 ][ 1 ]) + (1.0f * m.m[ 3 ][ 1 ]),
		(v.x * m.m[ 0 ][ 2 ]) + (v.y * m.m[ 1 ][ 2 ]) + (v.z * m.m[ 2 ][ 2 ]) + (1.0f * m.m[ 3 ][ 2 ])
	};
	float w = (v.x * m.m[ 0 ][ 3 ]) + (v.y * m.m[ 1 ][ 3 ]) + (v.z * m.m[ 2 ][ 3 ]) + (1.0f * m.m[ 3 ][ 3 ]);

	//0除算を避ける
	if ( w != 0.0f ) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return result;
}


/// <summary>
/// Luaからカメラのデータをロードする
/// </summary>
void PlayerCamera::LoadCameraDataFromLua()
{
	//回転
	rotate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCamera.rotate");
	//座標
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCamera.translate");
	// オフセット
	offset_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCamera.offset");
}


/// <summary>
/// Imgui関連
/// </summary>
void PlayerCamera::ImGuiFunc()
{
	ImGui::DragFloat3("Offset", &offset_.x, 0.1f);
}
