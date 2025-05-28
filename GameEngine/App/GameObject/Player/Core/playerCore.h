#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "Move/PlayerMoveFunc.h"

#include "Attack/Interface/IMagicAttack.h"
#include "Attack/Basic/DemoBasic/PlayerAttackDemoBasic.h"
#include "../Projectile/PlayerProjectileManager.h"

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
	void KeyMove(const Math::Vector::Vec2 & input);

	/// <summary>
	/// ベーシック攻撃
	/// </summary>
	void BasicAttack();

	/// <summary>
	/// スタンダード攻撃
	/// </summary>
	void StandardAttack();

	/// <summary>
	/// シグネチャー攻撃
	/// </summary>
	void SignatureAttack();

	void OnCollision(std::weak_ptr<ObjectComponent> other);

#pragma region Accessor

	// ワールド座標の取得
	inline Math::Vector::Vec3 GetWorldPos() const {
		return ObjectComponent::gameObject_->GetWorldPos();
	}

	// カメラのweak_ptrの設定
	inline void SetCameraPtr(std::weak_ptr<PlayerCamera> camera) {
		weakpCamera_ = camera;
		moveFunc_->SetCameraPtr(camera);
	}

	// プレイヤーの向いている方向
	inline Math::Vector::Vec3 GetDirection() {
		return {
			std::sinf(rotate_.y),
			0.0f,
			std::cosf(rotate_.y),
		};
	}

#pragma endregion

private:

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

	// 攻撃コマンド
    std::array<std::unique_ptr<IMagicAttack>, 3> attacks_;

	// 発射物管理クラス
    std::unique_ptr<PlayerProjectileManager> projManager_;
};