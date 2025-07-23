#pragma once

#include "CLEYERA.h"
#include "Lua/Script/LuaScript.h"

#include "../Helper/PlayerHelper.h"

#include "../Command/PlayerCommandHandler.h"

#include "../State/Action/Interface/IPlayerActionState.h"
#include "../State/Action/LowAttack/PlayerLowAttackState.h"

#include "Move/PlayerMoveFunc.h"
#include "Dash/PlayerDashFunc.h"
#include "Invincible/PlayerInvincibleFunc.h"

#include "../Attack/Interface/IMagicAttack.h"
#include "../Attack/Low/Normal/LowAttack_Normal.h"
#include "../Attack/Low/Back/LowAttack_Back.h"
#include "../Attack/High/Normal/HighAttack_Normal.h"
#include "../Attack/Special/Normal/SpecialAttack_Normal.h"
#include "../Attack/Special/Power/SpecialAttack_Power.h"
#include "../Attack/Manager/PlayerBulletManager.h"

// 前方宣言
class PlayerCamera;
class ItemManager;
class EnemyManager;

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
	/// ImGuiの表示
	/// </summary>
	void ImGuiUpdate() override;

	/// <summary>
	/// 衝突時コールバック
	/// </summary>
	void OnCollision(std::weak_ptr<ObjectComponent> other);

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
	/// Stateの変更
	/// </summary>
	void ChangeActionState(std::unique_ptr<IPlayerActionState> newState);


#pragma region Accessor

	// Ptrの設定
	inline void SetPtr(std::weak_ptr<PlayerCamera> cameraptr,
		std::weak_ptr<PlayerBulletManager> bulManPtr,
		std::weak_ptr<ItemManager> itemMgr,
		std::weak_ptr<EnemyManager> enemyMgr)
	{
		weakpCamera_ = cameraptr;
		moveFunc_->SetCameraPtr(cameraptr);
		bulletManager_ = bulManPtr;
		itemMgr_ = itemMgr;
		enemyManager_ = enemyMgr;
	}

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

	// 各ベクトルの取得
	inline Math::Vector::Vec3 GetForwardVec() const
	{
		Math::Vector::Vec3 def = Math::Vector::Vec3{ 0.0f, 0.0f, 1.0f };
		return PlayerHelper::CalcDirectVec(def, rotate_.y);
	}
	inline Math::Vector::Vec3 GetBackVec() const
	{
		Math::Vector::Vec3 def = Math::Vector::Vec3{ 0.0f, 0.0f, -1.0f };
		return PlayerHelper::CalcDirectVec(def, rotate_.y);
	}
	inline Math::Vector::Vec3 GetRightVec() const
	{
		Math::Vector::Vec3 def = Math::Vector::Vec3{ 1.0f, 0.0f, 0.0f };
		return PlayerHelper::CalcDirectVec(def, rotate_.y);
	}
	inline Math::Vector::Vec3 GetLeftVec() const
	{
		Math::Vector::Vec3 def = Math::Vector::Vec3{ -1.0f, 0.0f, 0.0f };
		return PlayerHelper::CalcDirectVec(def, rotate_.y);
	}

	// hp計算関数をセット
	void SetHpCalcfunc(std::function<void(int32_t)> hpCalcFunc) { hpCalcFunc_ = hpCalcFunc; };

	// 攻撃後か
	bool IsAttacked() const { return isAttackStiff_; }

#pragma endregion

private:

	/// <summary>
	/// Luaの初期化
	/// </summary>
	void InitLua();

	/// <summary>
	/// Modelの初期化
	/// </summary>
	void InitModel();

	/// <summary>
	/// Colliderの初期化
	/// </summary>
	void InitCollider();

	/// <summary>
	/// Handlerの初期化
	/// </summary>
	void InitHandlers();

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
	// EnemyManagerのweak_ptr
	std::weak_ptr<EnemyManager> enemyManager_;

	// PlayerCoreのLua
	std::unique_ptr<LuaScript> lua_;

	// 移動処理
	std::unique_ptr<PlayerMoveFunc> moveFunc_;
	// ダッシュ処理
	std::unique_ptr<PlayerDashFunc> dashFunc_;
	// 無敵時間
	std::unique_ptr<PlayerInvincibleFunc> invincibleFunc_;

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