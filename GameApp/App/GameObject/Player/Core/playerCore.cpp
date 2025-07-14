#include "playerCore.h"
#include "../Camera/PlayerCamera.h"
#include "Wall/Wall.h"

#include "Enemy/Normal/Normal1/NormalEnemy1Bullet.h"
#include "Enemy/Normal/Normal2/NormalEnemy2Bullet.h"

#include "../../Item/Manager/ItemManager.h"
#include "../../Item/AttackPickup/AttackPickupItem.h"
#include "../../Item/Heal/HealItem.h"

PlayerCore::PlayerCore(std::weak_ptr<PlayerCamera> cameraptr, std::weak_ptr<PlayerBulletManager> bulManPtr, std::weak_ptr<ItemManager> itemMgr) {
	lua_ = std::make_unique<LuaScript>();
	commandHandler_ = std::make_unique<PlayerCommandHandler>(this);
	moveFunc_ = std::make_unique<PlayerMoveFunc>(this);
	moveFunc_->SetCameraPtr(cameraptr);
	bulletManager_ = bulManPtr;
	itemMgr_ = itemMgr;
}

void PlayerCore::Init() {
	// クラス名
	ObjectComponent::name_ = VAR_NAME(PlayerCore);

	// Luaの読み込み
	lua_->LoadScript("Player/Core", "PlayerCore");
	lua_->SetReloadCallBack([this]() { LoadCoreDataFromLua(); });

	// Luaから抽出したデータの設定
	LoadCoreDataFromLua();

	// Modelの設定
	uint32_t handle =
		ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
	ObjectComponent::gameObject_->ChangeModel(handle);
	uint32_t demo = ObjectComponent::modelManager_->LoadModel("Resources/Model/Player/DemoBullet",
															  "PlayerDemoBullet");
	demo;

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::AABB);
	// 当たり判定関数セット
	collider_->SetHitCallFunc(
		[this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });


	// コマンドハンドラー
	commandHandler_->Init();

	// Stateの初期化
	//ChangeActionState(std::make_unique<nullptr>());

	// 移動処理クラスの初期化
	moveFunc_->Init();

	// 攻撃スロットの初期化
	InitAttackSlot();
}

void PlayerCore::Update() {
	ObjectComponent::TransformUpdate();

	// ハンドラー
	commandHandler_->Handle();
	commandHandler_->Exec();

	// State
	if ( state_ ) {
		state_->Update();
	}

	// 移動処理クラス
	moveFunc_->Update();
	// 移動硬直のタイマー処理
	StiffMove();

	// 攻撃クラスの更新
	for ( auto & atk : attacks_ ) {
		if ( atk )
			atk->Update();
	}

	// ノックバック
	// 前方&右方のベクトルを求める
	CalcDirectVec();

	// ノックバック
	KnockBack();

	if ( translate_.y <= -2.0f ) {
		translate_ = { 0.0f, 1.0f, 0.0f };
	}
}

void PlayerCore::PadMove()
{ 
	moveFunc_->PadMove();
}

void PlayerCore::KeyMove(const Math::Vector::Vec2 & input)
{
	moveFunc_->KeyMove(input);
}

void PlayerCore::BasicAttack() 
{ 
	attacks_[ ToIndex(AttackType::Basic) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::StandardAttack() 
{ 
	attacks_[ ToIndex(AttackType::Standard) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::SignatureAttack()
{ 
	attacks_[ ToIndex(AttackType::Signature) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::Dash()
{

}

void PlayerCore::OnCollision([[maybe_unused]] std::weak_ptr<ObjectComponent> other) {
	auto obj = other.lock();

	if ( !obj ) {
		return;
	}
	// 今後dynamicから変更する

	// Wall 型にキャストできるかをチェック
	if ( auto wall = std::dynamic_pointer_cast< Wall >(obj) ) {
		// Wall にぶつかったときの処理
		auto aabb =
			std::dynamic_pointer_cast< CLEYERA::Util::Collider::AABBCollider >(wall->GetCollder().lock());
		// 押し出し
		this->translate_ -= aabb->GetAABB().push;
	}

	// bullet1 型にキャストできるかをチェック
	if ( auto bullet1 = std::dynamic_pointer_cast< NormalEnemy1Bullet >(obj) ) {

		hpCalcFunc_(bullet1->GetAttackPower());
	}

	// bullet2 型にキャストできるかをチェック
	if ( auto bullet2 = std::dynamic_pointer_cast< NormalEnemy2Bullet >(obj) ) {

		hpCalcFunc_(bullet2->GetAttackPower());
	}

	// HealItem 型にキャストできるかチェック
	if ( auto healItem = std::dynamic_pointer_cast< HealItem >(obj) ) {

	}
}

void PlayerCore::InitAttackSlot() {

	// 初期攻撃スロット
	attacks_[ ToIndex(AttackType::Basic) ] =
		std::make_unique<LowAttack_Normal>(this, bulletManager_);
	attacks_[ ToIndex(AttackType::Standard) ] =
		std::make_unique<HighAttack_Normal>(this, bulletManager_);
	attacks_[ ToIndex(AttackType::Signature) ] =
		std::make_unique<SpecialAttack_Normal>(this, bulletManager_);

	// 初期化
	for ( auto & atk : attacks_ ) {
		atk->Init();
	}
}

void PlayerCore::StiffMove()
{
	if ( isAttackStiff_) {
		attackStiffTimer_--; // インクリメント

		if ( attackStiffTimer_ <= 0.0f ) {
			isAttackStiff_ = false;
			attackStiffTimer_ = attackStiffDuration_;
		}
	}
}

void PlayerCore::LoadCoreDataFromLua() {
	translate_ = lua_->GetVariable<Math::Vector::Vec3>("PlayerCore.translate");
}

void PlayerCore::KnockBack() {
	// ランダムの値で位置を決める
	// SRは固定
	std::uniform_real_distribution<float_t> distribute(-1.0f, 1.0f);
	// ランダムエンジン
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	if ( isKnockBack_ == true ) {
		Math::Vector::Vec3 knockBackDirection = {};
		if ( isDesidePosition_ == false ) {
			knockBackDirection = {
				.x = distribute(randomEngine), .y = 0.0f, .z = distribute(randomEngine) };
			beforeKnockBackPosition_ = translate_;
			afterKnockBackPosition_ =
				beforeKnockBackPosition_ + knockBackDirection * KNOCK_BACK_DISTANCE_;
			isDesidePosition_ = true;
		}

		// ノックバックの時間
		knockBackTime_ += DELTA_TIME_;
		// 線形補間
		knockbackT_ += INCREASE_T_VALUE_;
		// 座標を線形補間でやるよ！
		translate_ =
			Math::Vector::Func::Lerp(beforeKnockBackPosition_, afterKnockBackPosition_, knockbackT_);
		knockbackT_ = std::clamp(knockbackT_, 0.0f, 1.0f);

		// 制限を超えたら0に戻る
		if ( knockbackT_ >= 1.0f ) {
			beforeKnockBackPosition_ = {};
			afterKnockBackPosition_ = {};

			knockBackTime_ = 0.0f;
			knockbackT_ = 0.0f;
			isKnockBack_ = false;
			isDesidePosition_ = false;
		}
	}
}

void PlayerCore::CalcDirectVec() {
	// 前方ベクトルのデフォルト値
	Math::Vector::Vec3 defForwardVec = Math::Vector::Vec3{ 0.0f, 0.0f, 1.0f };
	// 後方ベクトルのデフォルト値
	Math::Vector::Vec3 defBackVec = Math::Vector::Vec3{ 0.0f, 0.0f, -1.0f };
	// 右方ベクトルのデフォルト値
	Math::Vector::Vec3 defRightVec = Math::Vector::Vec3{ 1.0f, 0.0f, 0.0f };
	// 左方ベクトルのデフォルト値
	Math::Vector::Vec3 defLeftVec = Math::Vector::Vec3{ -1.0f, 0.0f, 0.0f };

	// Y軸の回転行列
	Math::Matrix::Mat4x4 rotateYMat = Math::Matrix::Func::RotateYMatrix(rotate_.y);

	// 前方ベクトルを求める
	forwardVec_ = TransformWithPerspective(defForwardVec, rotateYMat);
	// 上方ベクトルを求める
	backVec_ = TransformWithPerspective(defBackVec, rotateYMat);
	// 右方ベクトルを求める
	rightVec_ = TransformWithPerspective(defRightVec, rotateYMat);
	// 左方ベクトルを求める
	leftVec_ = TransformWithPerspective(defLeftVec, rotateYMat);
}

Math::Vector::Vec3 PlayerCore::TransformWithPerspective(const Math::Vector::Vec3 & v,
														const Math::Matrix::Mat4x4 & m) {
	Math::Vector::Vec3 result = {
		(v.x * m.m[ 0 ][ 0 ]) + (v.y * m.m[ 1 ][ 0 ]) + (v.z * m.m[ 2 ][ 0 ]) + (1.0f * m.m[ 3 ][ 0 ]),
		(v.x * m.m[ 0 ][ 1 ]) + (v.y * m.m[ 1 ][ 1 ]) + (v.z * m.m[ 2 ][ 1 ]) + (1.0f * m.m[ 3 ][ 1 ]),
		(v.x * m.m[ 0 ][ 2 ]) + (v.y * m.m[ 1 ][ 2 ]) + (v.z * m.m[ 2 ][ 2 ]) + (1.0f * m.m[ 3 ][ 2 ]) };
	float w = (v.x * m.m[ 0 ][ 3 ]) + (v.y * m.m[ 1 ][ 3 ]) + (v.z * m.m[ 2 ][ 3 ]) + (1.0f * m.m[ 3 ][ 3 ]);

	// 0除算を避ける
	if ( w != 0.0f ) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return result;
}


void PlayerCore::ChangeActionState(std::unique_ptr<IPlayerActionState> newState)
{
	if(state_ ) state_->Exit();
	state_ = std::move(newState);
	state_->Enter(this);
}

void PlayerCore::ImGuiUpdate()
{
	if ( ImGui::TreeNode("PlayerCore") ) {

		if ( ImGui::Button("Pop AttackpickupItem ") ) {

		}

		ImGui::TreePop();
	}
}