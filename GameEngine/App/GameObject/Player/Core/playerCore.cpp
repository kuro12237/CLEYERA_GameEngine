#include "playerCore.h"



/// <summary>
/// コンストラク
/// </summary>
PlayerCore::PlayerCore() 
{
	lua_ = std::make_unique<LuaScript>();
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerCore::Init()
{
	// クラス名
	ObjectComponent::name_ = VAR_NAME(PlayerCore);

	// Luaの読み込み
	lua_->LoadScript("LuaScript/Player/Core", "PlayerCore.lua");
	lua_->SetReloadCallBack([this]() {LoadCoreDataFromLua(); });

	// Luaから抽出したデータの設定
	LoadCoreDataFromLua();

	// Modelの設定
	std::pair<std::string, std::string> str = {	"Resources/Model/Player/Core", "Core" };
	uint32_t handle = ObjectComponent::modelManager_->LoadModel(str.first, str.second);
	ObjectComponent::gameObject_->ChangeModel(handle);

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::OBB);

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerCore::Update()
{
	TransformUpdate();
}


/// <summary>
/// 移動処理
/// </summary>
void PlayerCore::Move()
{
	Math::Vector::Vec2 joyR = inputManager_->JoyLPos();
	Math::Vector::Vec2 speed = { 1.0f, 1.0f };
	Math::Vector::Vec2 result = joyR * speed;
	force_.x = result.x;
	force_.z = result.y;

	if ( inputManager_->PushBotton(XINPUT_GAMEPAD_RIGHT_SHOULDER) ) {
		force_.x *= 0.1f;
		force_.z *= 0.1f;
	}
}


/// <summary>
/// 進行方向に向く処理
/// </summary>
void PlayerCore::FaceMovementDirection()
{
}


/// <summary>
/// Luaからデータを抽出する
/// </summary>
void PlayerCore::LoadCoreDataFromLua()
{
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}
