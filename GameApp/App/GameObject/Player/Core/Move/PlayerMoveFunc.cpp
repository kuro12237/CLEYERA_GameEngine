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
	// Luaの読み込み
	lua_->LoadScript("Player/Move", "PlayerMove");
	lua_->SetReloadCallBack([this]() {LoadDataFromLua(); });
	// データの設定
	LoadDataFromLua();

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerMoveFunc::Update()
{
	// Padの入力状況
	LStickInput_ = inputManager_->JoyLPos();

	// 移動方向の計算
	CalcMoveDirection();

	// 0で初期化 この処理は一番最後にやらないとダメ
	keyDir_ = Math::Vector::Vec3{ 0.0f, 0.0f, 0.0f };

#ifdef _DEBUG
	lua_->MonitorScript();
#endif // _DEBUG
}


/// <summary>
/// Padの移動処理
/// </summary>
void PlayerMoveFunc::PadMove()
{
	if ( std::abs(LStickInput_.x) > LStickDzone_ || std::abs(LStickInput_.y) > LStickDzone_ ) {
		
		// カメラの前方と右方
		Math::Vector::Vec3 forward = weakpCamera_.lock()->GetForwardVec();
		Math::Vector::Vec3 right = weakpCamera_.lock()->GetRightVec();
		
		// カメラの向きを考慮したDirectionを求める
		padDir_ = {
			(LStickInput_.x * right.x) + (LStickInput_.y * forward.x),
			0.0f,
			(LStickInput_.x * right.z) + (LStickInput_.y * forward.z),
		};

		// PlayerMoveFunc::PadMove などで移動力を補間して設定
		Math::Vector::Vec3 targetForce = Math::Vector::Func::Normalize(padDir_);
		float turningAngle = CalcTurningAngle(targetForce);
		float speedScale = TurningSpeedScale(turningAngle);

		// スピードスケール適用
		targetForce = targetForce * (speedScale * maxSpeed_);  // maxSpeed_ は最大移動速度

		// 現在の force を滑らかに補間
		currentForce_ = Math::Vector::Func::Lerp(currentForce_, targetForce, inertiaFactor_);

		// プレイヤーに設定
		p_player_->SetForce(currentForce_);
	}

	// 姿勢を合わせる
	CalcBodyOrientation(LStickInput_, padDir_);
}


/// <summary>
/// Keyの移動処理
/// </summary>
void PlayerMoveFunc::KeyMove(const Math::Vector::Vec2 & input)
{
	// 入力状況の取得 引数のDirをそのまま入れて大丈夫
	keyInput_ = input;

	// カメラの前方と右方
	Math::Vector::Vec3 forward = weakpCamera_.lock()->GetForwardVec();
	Math::Vector::Vec3 right = weakpCamera_.lock()->GetRightVec();
	
	// カメラの向きを考慮したDirectionを求める
	keyDir_ = {
		(keyInput_.x * right.x) + (keyInput_.y * forward.x),
		0.0f,
		(keyInput_.x * right.z) + (keyInput_.y * forward.z),
	};

	// PlayerMoveFunc::PadMove などで移動力を補間して設定
	Math::Vector::Vec3 targetForce = Math::Vector::Func::Normalize(keyDir_);
	float turningAngle = CalcTurningAngle(targetForce);
	float speedScale = TurningSpeedScale(turningAngle);

	// スピードスケール適用
	targetForce = targetForce * (speedScale * maxSpeed_);  // maxSpeed_ は最大移動速度

	// 現在の force を滑らかに補間
	currentForce_ = Math::Vector::Func::Lerp(currentForce_, targetForce, inertiaFactor_);

	// プレイヤーに設定
	p_player_->SetForce(currentForce_);

	// 姿勢を合わせる
	CalcBodyOrientation(keyInput_, keyDir_);
}


/// <summary>
/// 移動方向を求める
/// </summary>
void PlayerMoveFunc::CalcMoveDirection()
{
	// カメラの前方と右方
	Math::Vector::Vec3 forward = weakpCamera_.lock()->GetForwardVec();
	Math::Vector::Vec3 right = weakpCamera_.lock()->GetRightVec();

	// LStickの移動方向を求める
	padDir_ = {
		(LStickInput_.x * right.x) + (LStickInput_.y * forward.x),
		(LStickInput_.x * right.z) + (LStickInput_.y * forward.z),
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
		current.y = Math::Vector::Func::Lerp(current.y, current.y + shortest, rotateLerp);
		// 設定 
		p_player_->SetRotate(current);
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
/// 現在の向きと移動方向の角度差を求める
/// </summary>
float PlayerMoveFunc::CalcTurningAngle(const Math::Vector::Vec3 & moveDir)
{
	Math::Vector::Vec3 currentForward = p_player_->GetDirection();
	Math::Vector::Vec3 moveNorm = Math::Vector::Func::Normalize(moveDir);

	// 点積で角度を求める
	float dot = Math::Vector::Func::Dot(currentForward, moveNorm);
	dot = std::clamp(dot, -1.0f, 1.0f);

	float angle = std::acos(dot); // ラジアン
	return angle; // 0〜π
}


/// <summary>
/// 角度に応じた速度スケールの計算
/// </summary>
float PlayerMoveFunc::TurningSpeedScale(float angle)
{
	const float maxAngle = 3.14159265f; // π = 180度
	return std::lerp(1.0f, minSpeedScale_, angle / maxAngle);
}


/// <summary>
/// Luaからデータを読み込む
/// </summary>
void PlayerMoveFunc::LoadDataFromLua()
{
	LStickDzone_ = lua_->GetVariable<float>("PlayerMove.LStickDeadZone");
	maxSpeed_ = lua_->GetVariable<float>("PlayerMove.maxSpeed");
	inertiaFactor_ = lua_->GetVariable<float>("PlayerMove.inertiaFactor");
	minSpeedScale_ = lua_->GetVariable<float>("PlayerMove.minSpeedScale");
	rotateLerp = lua_->GetVariable<float>("PlayerMove.rotateLerp");
}

