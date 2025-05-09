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
/// Luaからデータを抽出する
/// </summary>
void PlayerCore::LoadCoreDataFromLua()
{
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}
