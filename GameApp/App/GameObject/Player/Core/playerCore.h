#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "../Command/PlayerCommandHandler.h"

#include "../State/Action/Interface/IPlayerActionState.h"
#include "../State/Action/LowAttack/PlayerLowAttackState.h"

#include "Move/PlayerMoveFunc.h"

#include "../Attack/Interface/IMagicAttack.h"
#include "../Attack/Low/Normal/LowAttack_Normal.h"
#include "../Attack/Low/Back/LowAttack_Back.h"
#include "../Attack/High/Normal/HighAttack_Normal.h"
#include "../Attack/Special/Normal/SpecialAttack_Normal.h"
#include "../Attack/Manager/PlayerBulletManager.h"

// 前方宣言
class PlayerCamera;
class ItemManager;

/* Playerの実体クラス */
class PlayerCore : public CLEYERA::Component::ObjectComponent {

public:
	/// <summary>
	/// コンストラク
	/// </summary>
	PlayerCore() = default;
	PlayerCore(std::weak_ptr<PlayerCamera> cameraptr, std::weak_ptr<PlayerBulletManager> bulManPtr, std::weak_ptr<ItemManager> itemMgr);

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

	/// <summary>
	/// ダッシュ
	/// </summary>
	void Dash();

	/// <summary>
	/// 衝突時コールバック
	/// </summary>
	void OnCollision(std::weak_ptr<ObjectComponent> other);

	/// <summary>
	/// Stateの変更
	/// </summary>
	void ChangeActionState(std::unique_ptr<IPlayerActionState> newState);

	void ImGuiUpdate() override;

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

	/// <summary>
	/// hp計算関数をセット
	/// </summary>
	void SetHpCalcfunc(std::function<void(int32_t)> hpCalcFunc) { hpCalcFunc_ = hpCalcFunc; };

	// 前方ベクトルの取得
	Math::Vector::Vec3 GetForwardVec() const { return forwardVec_; }
	// 後方ベクトルの取得
	Math::Vector::Vec3 GetBackVec() const { return backVec_; }
	// 右方ベクトルの取得
	Math::Vector::Vec3 GetRightVec() const { return rightVec_; }
	// 左方ベクトルの取得
	Math::Vector::Vec3 GetLeftVec() const { return leftVec_; }

	// 攻撃後か
	bool IsAttacked() const { return isAttackStiff_; }

#pragma endregion

private:
	/// <summary>
	/// 攻撃スロットの初期化
	/// </summary>
	void InitAttackSlot();

	/// <summary>
	/// 移動硬直処理
	/// </summary>
	void StiffMove();

	/// <summary>
	/// Luaからデータを抽出する
	/// </summary>
	void LoadCoreDataFromLua();

	/// <summary>
	/// 方向ベクトルを求める
	/// </summary>
	void CalcDirectVec();

	/// <summary>
	/// Vector3にアフィン変換と透視補正を適用する
	/// </summary>
	Math::Vector::Vec3 TransformWithPerspective(const Math::Vector::Vec3 & v,
												const Math::Matrix::Mat4x4 & m);

	/// <summary>
	/// ノックバック
	/// </summary>
	void KnockBack();

private:
	/// <summary>
	/// hp計算関数ポインタ
	/// </summary>
	/// <param name="power"></param>
	/// <returns></returns>
	std::function<void(int32_t)> hpCalcFunc_;
	// ノックバックの距離
	const float_t KNOCK_BACK_DISTANCE_ = 5.0f;
	// 時間変化
	const float_t DELTA_TIME_ = 1.0f / 60.0f;
	// 線形補間
	const float_t INCREASE_T_VALUE_ = 0.1f;
	// 最大ノックバック時間
	const float_t MAX_KNOCK_BACK_TIME_ = 3.0f;

private:

	// CommandHandler
	std::unique_ptr<PlayerCommandHandler> commandHandler_;
	
	// State
	std::unique_ptr<IPlayerActionState> actionState_;

	// ItemManagerのweak_ptr
	std::weak_ptr<ItemManager> itemMgr_;

	// Cameraのweak_ptr
	std::weak_ptr<PlayerCamera> weakpCamera_;

	// PlayerCoreのLua
	std::unique_ptr<LuaScript> lua_;

	// 移動処理
	std::unique_ptr<PlayerMoveFunc> moveFunc_;

	// 攻撃コマンド
	std::array<std::unique_ptr<IMagicAttack>, 3> attacks_;

	// 弾管理クラス
	std::weak_ptr<PlayerBulletManager> bulletManager_;

	// 前方&右方ベクトル
	Math::Vector::Vec3 forwardVec_{};
	Math::Vector::Vec3 backVec_{};
	Math::Vector::Vec3 rightVec_{};
	Math::Vector::Vec3 leftVec_{};

	// 攻撃後の硬直
	bool isAttackStiff_ = false;
	float attackStiffTimer_ = 0.0f;
	float attackStiffDuration_ = 10.0f; // 0.3秒硬直

	// ノックバック
	bool isKnockBack_ = false;
	// 時間
	float_t knockBackTime_ = 0.0f;
	// 線形補間
	float_t knockbackT_ = 0.0f;
	// 方向を決める
	bool isDesidePosition_ = false;

	// ノックバック前の座標
	Math::Vector::Vec3 beforeKnockBackPosition_ = {};
	// ノックバック後の座標
	Math::Vector::Vec3 afterKnockBackPosition_ = {};
};