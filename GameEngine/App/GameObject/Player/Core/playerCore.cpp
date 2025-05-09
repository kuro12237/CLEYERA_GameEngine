#include "playerCore.h"
#include "../Camera/PlayerCamera.h"


/// <summary>
/// コンストラク
/// </summary>
PlayerCore::PlayerCore()
{
	lua_ = std::make_unique<LuaScript>();
	moveFunc_ = std::make_unique<PlayerMoveFunc>(this);
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerCore::Init()
{
	// クラス名
	ObjectComponent::name_ = VAR_NAME(PlayerCore);

	// Luaの読み込み
	lua_->LoadScript("Player/Core", "PlayerCore");
	lua_->SetReloadCallBack([this]() {LoadCoreDataFromLua(); });

	// Luaから抽出したデータの設定
	LoadCoreDataFromLua();

	// Modelの設定
	std::pair<std::string, std::string> str = { "Resources/Model/Player/Core", "Core" };
	uint32_t handle = ObjectComponent::modelManager_->LoadModel(str.first, str.second);
	ObjectComponent::gameObject_->ChangeModel(handle);

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::OBB);

	// 移動処理クラスの初期化
	moveFunc_->Init();

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerCore::Update()
{
	TransformUpdate();

	// 移動処理クラス
	moveFunc_->Update();
}


/// <summary>
/// Padの移動処理
/// </summary>
void PlayerCore::PadMove()
{
	moveFunc_->PadMove();
}


/// <summary>
/// Keyの移動処理
/// </summary>
void PlayerCore::KeyMove(const Math::Vector::Vec2 & input)
{
	moveFunc_->KeyMove(input);
}


/// <summary>
/// Luaからデータを抽出する
/// </summary>
void PlayerCore::LoadCoreDataFromLua()
{
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}
