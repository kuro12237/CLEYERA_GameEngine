#include "PlayerMoveFunc.h"
#include "../playerCore.h"
#include "../../Camera/PlayerCamera.h"
#include "imgui.h"


/// <summary>
/// コンストラク
/// </summary>
PlayerMoveFunc::PlayerMoveFunc(PlayerCore * pPlayer)
{
	// 入力デバイス
	inputManager_ = CLEYERA::Manager::InputManager::GetInstance();
	
	// 親プレイヤー
	p_player_ = pPlayer;

	// Luaスクリプト
	lua_ = std::make_unique<LuaScript>();
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerMoveFunc::Init()
{

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerMoveFunc::Update()
{
	// 移動方向の計算
	CalcMoveDirection();

#ifdef _DEBUG
	//lua_->MonitorScript();
	DrawImGui();
#endif // _DEBUG

	// 0で初期化
	keyDir_ = Math::Vector::Vec3{ 0.0f, 0.0f, 0.0f };
}


/// <summary>
/// Padの移動処理
/// </summary>
void PlayerMoveFunc::PadMove()
{
	// stickrの入力状況
	Math::Vector::Vec2 joyL = inputManager_->JoyLPos();

	if ( std::abs(joyL.x) > LStickDzone_ || std::abs(joyL.y) > LStickDzone_ ) {
		// 移動
		// 移動方向を正規化
		Math::Vector::Vec3 force = Math::Vector::Func::Normalize(padDir_);
		p_player_->SetForce(force);
	}

	// 姿勢を合わせる
	CalcBodyOrientation(joyL, padDir_);
}


/// <summary>
/// 移動方向を求める
/// </summary>
void PlayerMoveFunc::CalcMoveDirection()
{
	// カメラの前方と右方
	Math::Vector::Vec3 forward = weakpCamera_.lock()->GetForwardVec();
	Math::Vector::Vec3 right = weakpCamera_.lock()->GetRightVec();
	// LStickの傾き
	Math::Vector::Vec2 joyL = inputManager_->JoyLPos();

	// LStickの移動方向を求める
	padDir_ = {
		(joyL.x * right.x) + (joyL.y * forward.x),
		(joyL.x * right.z) + (joyL.y * forward.z),
	};
	keyDir_ = {
		(keyDir_.x * right.x) + (keyDir_.z * forward.x),
		(keyDir_.x * right.z) + (keyDir_.z * forward.z),
	};
}


/// <summary>
/// 移動方向からY軸の姿勢を合わせる
/// </summary>
void PlayerMoveFunc::CalcBodyOrientation(const Math::Vector::Vec2 & input, const Math::Vector::Vec3 & dir)
{
	if ( std::abs(input.x) > LStickDzone_ || std::abs(input.y) > LStickDzone_ ) {

		// 正規化した移動方向
		Math::Vector::Vec3 normalDir =
			Math::Vector::Func::Normalize(dir);
		// 目標回転角度
		float target = std::atan2(normalDir.x, normalDir.z);
		// 現在の角度と目標角度から最短を求める
		// 現在の角度
		Math::Vector::Vec3 current = p_player_->GetGameObject().lock()->GetRotate();
		float shortest = ShortestAngle(current.y, target);
		// 現在の角度と最短角度の間を補間
		current.y = Math::Vector::Func::Lerp(current.y, current.y + shortest, 1.0f);
	}
}


/// <summary>
/// 最短回転角度を求める
/// </summary>
float PlayerMoveFunc::ShortestAngle(float current, float target)
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
/// ImGuiの描画
/// </summary>
void PlayerMoveFunc::DrawImGui()
{
	if ( ImGui::TreeNode("MoveFunc") ) {
		ImGui::DragFloat2("KeyDir", &keyDir_.x, 0.0f, 0.0f, 1.0f);
		ImGui::TreePop();
	}
}
