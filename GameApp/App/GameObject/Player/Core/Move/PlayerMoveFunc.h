#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

// 前方宣言
class PlayerCore;
class PlayerCamera;

/* Playerの移動処理クラス */
class PlayerMoveFunc {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerMoveFunc(PlayerCore* pPlayer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerMoveFunc() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// Padの移動処理
	/// </summary>
	void PadMove();

	/// <summary>
	/// Keyの移動処理
	/// </summary>
	void KeyMove(const Math::Vector::Vec2 & input);

#pragma region Accessor

	// カメラのweak_ptrの設定
	void SetCameraPtr(std::weak_ptr<PlayerCamera> camera) {
		weakpCamera_ = camera;
	}

#pragma endregion


public:

	/// <summary>
	/// 移動方向を求める
	/// </summary>
	void CalcMoveDirection();

	/// <summary>
	/// 移動方向からY軸の姿勢を合わせる
	/// </summary>
	void CalcBodyOrientation(const Math::Vector::Vec2 & input, const Math::Vector::Vec3& dir);

	/// <summary>
	/// 最短回転角度を求める
	/// </summary>
	float ShortestAngle(float current, float target);

	/// <summary>
	/// 現在の向きと移動方向の角度差を求める
	/// </summary>
	float  CalcTurningAngle(const Math::Vector::Vec3 & moveDir);

	/// <summary>
	/// 角度に応じた速度スケールの計算
	/// </summary>
	float TurningSpeedScale(float angle);

	/// <summary>
	/// Luaからデータを読み込む
	/// </summary>
	void LoadDataFromLua();

private:

	// 入力デバイス
	CLEYERA::Manager::InputManager * inputManager_ = nullptr;

	// 親クラス
	PlayerCore* p_player_;

	// Cameraのweak_ptr
	std::weak_ptr<PlayerCamera> weakpCamera_;

	// スクリプト
	std::unique_ptr<LuaScript> lua_;

	// 速度力
	Math::Vector::Vec3 currentForce_{};

	// 最大速度
	float maxSpeed_ = 0.0f;

	// 慣性
	float inertiaFactor_ = 0.0f;

	// 方向転換時の最低速度スケール
	float minSpeedScale_ = 0.0f;
	
	// 姿勢補間率
	float rotateLerp = 0.0f;

	// 入力状況
	Math::Vector::Vec2 LStickInput_{};
	Math::Vector::Vec2 keyInput_{};

	// 移動方向
	Math::Vector::Vec3 padDir_{};
	Math::Vector::Vec3 keyDir_{};

	// Padの左stickのDeadZone
	float LStickDzone_ = 0.0f;
};
