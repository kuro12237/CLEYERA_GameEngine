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
