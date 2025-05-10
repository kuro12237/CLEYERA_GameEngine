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
	lua_->LoadScript("LuaScript/Player/Core", "PlayerCore.lua");
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
	Math::Vector::Vec2 joyL= inputManager_->JoyLPos();
	
	if ( std::abs(joyL.x) > LStickDzone_ || std::abs(joyL.y) > LStickDzone_ ) {
		
		// 移動量の計算
		force_ = Math::Vector::Func::Normalize(LStickMoveDirection_);		
	}
}


/// <summary>
/// Keyの移動処理
/// </summary>
void PlayerCore::KeyMove(const Math::Vector::Vec3 & dir)
{
	moveFunc_->KeyMove(dir);
}


/// <summary>
/// Keyの移動処理
/// </summary>
/// <summary>
/// 移動方向からY軸の姿勢を合わせる
/// </summary>
void PlayerCore::CalcBodyOrienation()
{
	// カメラの前方と右方
	Math::Vector::Vec3 forward = weakpCamera_.lock()->GetForwardVec();
	Math::Vector::Vec3 right = weakpCamera_.lock()->GetRightVec();
	// LStickの傾き
	Math::Vector::Vec2 joyL = inputManager_->JoyLPos();

	// LStickの移動方向を求める
	LStickMoveDirection_ = {
		(joyL.x * right.x) + (joyL.y * forward.x),
		0.0f,
		(joyL.x * right.z) + (joyL.y * forward.z),
	};

	// 正規化した移動方向
	Math::Vector::Vec3 normalizeDirection = Math::Vector::Func::Normalize(LStickMoveDirection_);

	// 目標回転角度
	float targetAngle = std::atan2(normalizeDirection.x, normalizeDirection.z);

	// 現在の角度と目標角度から最短を求める
	float shortestAngle = ShortestAngle(rotate_.y, targetAngle);

	// 現在の角度を目標角度の間を補間
	rotate_.y =
		Math::Vector::Func::Lerp(rotate_.y, rotate_.y + shortestAngle, 1.0f);
}


/// <summary>
/// 最短回転角度を求める
/// </summary>
float PlayerCore::ShortestAngle(float current, float target)
{
	// 角度の差を計算
	float angleDifference = target - current;

	// 角度を -π から +π の範囲に正規化する
	float PI = 3.1415926535897932384626433832795028f;
	while ( angleDifference > PI ) angleDifference -= 2.0f * PI;
	while ( angleDifference < -PI ) angleDifference += 2.0f * PI;

	return angleDifference; // 最短回転角度を返す
}


/// <summary>
/// Luaからデータを抽出する
/// </summary>
void PlayerCore::LoadCoreDataFromLua()
{
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}
