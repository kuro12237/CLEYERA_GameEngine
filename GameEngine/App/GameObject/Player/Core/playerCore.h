#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "Move/PlayerMoveFunc.h"


// 前方宣言
class PlayerCamera;

/* Playerの実体クラス */
class PlayerCore : public CLEYERA::Component::ObjectComponent {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCore();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCore() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// Padの移動処理
	/// </summary>
	void PadMove();

	/// <summary>
	/// Keyの移動処理
	/// </summary>
	void KeyMove(const Math::Vector::Vec3 & dir);

	/// <summary>
	/// 移動方向からY軸の姿勢を合わせる
	/// </summary>
	void CalcBodyOrienation();


#pragma region Accessor

	// ワールド座標の取得
	inline Math::Vector::Vec3 GetWorldPos() const {
		return ObjectComponent::gameObject_->GetWorldPos();
	}

	// カメラのweak_ptrの設定
	void SetCameraPtr(std::weak_ptr<PlayerCamera> camera) {
		weakpCamera_ = camera;
		moveFunc_->SetCameraPtr(camera);
	}

#pragma endregion


private:

	/// <summary>
	/// 最短回転角度を求める
	/// </summary>
	float ShortestAngle(float current, float target);

	/// <summary>
	/// Luaからデータを抽出する
	/// </summary>
	void LoadCoreDataFromLua();


private:

	// Cameraのweak_ptr
	std::weak_ptr<PlayerCamera> weakpCamera_;

	// PlayerCoreのLua
	std::unique_ptr<LuaScript> lua_;

	// 移動処理
	std::unique_ptr<PlayerMoveFunc> moveFunc_;

	// Pad移動方向
	Math::Vector::Vec3 LStickMoveDirection_{};
	// Padの左stickのDeadZone
	float LStickDzone_ = 0.0f;
	// Key移動方向
	Math::Vector::Vec3 keyMoveDirection_{};
};