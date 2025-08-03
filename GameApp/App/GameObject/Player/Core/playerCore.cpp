#include "playerCore.h"
#include "../Camera/PlayerCamera.h"
#include "Wall/Wall.h"
#include "../SkillUI/PlayerSkillUI_Manager.h"

#include "Enemy/EnemyManager.h"
#include "Enemy/Normal/Cannon/CannonNormalEnemy1Bullet.h"
#include "Enemy/Normal/Gun/GunNormalEnemyBullet.h"

#include "../../Item/Manager/ItemManager.h"
#include "../../Item/AttackPickup/AttackPickupItem.h"
#include "../../Item/Heal/HealItem.h"

PlayerCore::PlayerCore() 
{
	lua_ = std::make_unique<LuaScript>();
	commandHandler_ = std::make_unique<PlayerCommandHandler>(this);
	moveFunc_ = std::make_unique<PlayerMoveFunc>(this);
	dashFunc_ = std::make_unique<PlayerDashFunc>(this);
	invincibleFunc_ = std::make_unique<PlayerInvincibleFunc>(this);
}

void PlayerCore::Init() {
	// クラス名
	ObjectComponent::name_ = VAR_NAME(PlayerCore);

	InitLua();
	InitModel();
	InitCollider();
	InitHandlers();
	InitAttackSlot();

	hpComp_.lock()->SetMaxHP(50);
}

void PlayerCore::Update() {

	ObjectComponent::TransformUpdate();

	commandHandler_->Handle();
	commandHandler_->Exec();

	moveFunc_->Update();
	StiffMove(); // 移動硬直のタイマー処理
	dashFunc_->Update();
	invincibleFunc_->Update();

	for ( auto & atk : attacks_ ) {
		if ( atk )
			atk->Update();
	}

	CheckAttackUpgrade();

	// ノックバック
	KnockBack();

	if ( translate_.y <= -2.0f ) {
		translate_ = { 0.0f, 1.0f, 0.0f };
	}
}

void PlayerCore::ImGuiUpdate() {}

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
			std::dynamic_pointer_cast< CLEYERA::Util::Collider::AABBCollider >(wall->GetCollider().lock());
		// 押し出し
		this->translate_ -= aabb->GetAABB().push;
	}

	// HealItem 型にキャストできるかチェック
	if ( auto healItem = std::dynamic_pointer_cast< HealItem >(obj) ) {

	}

	// 無敵なので早期return
	if ( invincibleFunc_->IsInvincible() )
		return;

	// bullet1 型にキャストできるかをチェック
	if ( auto bullet1 = std::dynamic_pointer_cast< CannonNormalEnemy1Bullet >(obj) ) {

		uint32_t damage = bullet1->GetAttackPower();
		hpComp_.lock()->CalcHp(damage);
	}
	// bullet2 型にキャストできるかをチェック
	if ( auto bullet2 = std::dynamic_pointer_cast< GunNormalEnemyBullet >(obj) ) {

		uint32_t damage = bullet2->GetAttackPower();
		hpComp_.lock()->CalcHp(damage);
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
	attacks_[ ToIndex(AttackType::Low) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::StandardAttack() 
{ 
	attacks_[ ToIndex(AttackType::High) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::SignatureAttack()
{ 
	attacks_[ ToIndex(AttackType::Special) ]->IsAttack();
	isAttackStiff_ = true;
}

void PlayerCore::Dash()
{
	invincibleFunc_->AddInvTimer(0.2f);
	dashFunc_->StartDash();
}

void PlayerCore::InitLua()
{
	// Luaの読み込み
	lua_->LoadScript("Player/Core", "PlayerCore");
	lua_->SetReloadCallBack([this]() { LoadCoreDataFromLua(); });

	// Luaから抽出したデータの設定
	LoadCoreDataFromLua();
}

void PlayerCore::InitModel()
{
	// Modelの設定
	uint32_t handle = modelManager_->LoadModel("Resources/Model/Player/Core", "Core");
	gameObject_->ChangeModel(handle);
	uint32_t demo = modelManager_->LoadModel("Resources/Model/Player/Bullet", "Bullet");
	demo;
	uint32_t demo2 = modelManager_->LoadModel("Resources/Model/Player/Bullet2", "Bullet2");
	demo2;
}

void PlayerCore::InitCollider()
{
	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::AABB);
	// 当たり判定関数セット
	collider_->SetHitCallFunc(
		[this](std::weak_ptr<ObjectComponent> other) { this->OnCollision(other); });
}

void PlayerCore::InitHandlers()
{
	commandHandler_->Init();
	moveFunc_->Init();
	dashFunc_->Init();
	invincibleFunc_->Init();
}

void PlayerCore::InitAttackSlot() {

	// 初期攻撃スロット
	attacks_[ ToIndex(AttackType::Low) ] =
		std::make_unique<LowAttack_Normal>(this, bulletManager_, enemyManager_);

	attacks_[ ToIndex(AttackType::High) ] =
		std::make_unique<HighAttack_Normal>(this, bulletManager_, enemyManager_);

	attacks_[ ToIndex(AttackType::Special) ] =
		std::make_unique<SpecialAttack_Normal>(this, bulletManager_, enemyManager_);

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

void PlayerCore::CheckAttackUpgrade()
{
	if ( KillCount_Cannon_ >= 3 || killCount_Gun_  >= 3) {
		CheckLowAttackUpgrade();
	}
	if ( killCount_Donut_ >= 3) {
		CheckHighAttackUpgread();
	}
	if ( killCount_Stalker_ >= 3 ) {
		CheckSpecialAttackUpgread();
	}
}

void PlayerCore::CheckLowAttackUpgrade()
{
	if(lowAttack_Upgreaded_ ) return;

	attacks_[ ToIndex(AttackType::Low) ].reset();
	attacks_[ ToIndex(AttackType::Low) ] = 
		std::make_unique<LowAttack_Back>(this, bulletManager_, enemyManager_);

	attacks_[ToIndex(AttackType::Low) ]->Init();

	lowAttack_Upgreaded_ = true;

	// UIを変更
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::Low_Normal), false);
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::Low_Back), true);
}

void PlayerCore::CheckHighAttackUpgread()
{
	if ( highAttack_Upgreaded_ ) return;

	attacks_[ ToIndex(AttackType::High) ].reset();
	attacks_[ ToIndex(AttackType::High) ] =
		std::make_unique<HighAttack_Field>(this, bulletManager_, enemyManager_);

	attacks_[ ToIndex(AttackType::High) ]->Init();

	highAttack_Upgreaded_ = true;

	// UIを変更
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::High_Normal), false);
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::High_Field), true);
}

void PlayerCore::CheckSpecialAttackUpgread()
{
	if ( specialAttack_Upgreaded_ ) return;

	attacks_[ ToIndex(AttackType::Special) ].reset();
	attacks_[ ToIndex(AttackType::Special) ] =
		std::make_unique<SpecialAttack_Power>(this, bulletManager_, enemyManager_);

	attacks_[ ToIndex(AttackType::Special) ]->Init();

	specialAttack_Upgreaded_ = true;

	// UIを変更
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::Special_Normal), false);
	playerSkillMgr_.lock()->SetActive(int(PlayerSkillUI_Manager::SkillTypes::Special_Power), true);
}
