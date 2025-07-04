#include "LowAttack_Normal.h"
#include "LowAttack_NormalBullet.h"
#include "../../../Core/playerCore.h"

LowAttack_Normal::LowAttack_Normal(PlayerCore * corePtr, std::weak_ptr<PlayerBulletManager> bulManagerPtr)
{
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
	lua_ = std::make_unique<LuaScript>();
}

void LowAttack_Normal::Init()
{
	// コンボのMax
	comboMax_ = 3;
	// 攻撃ステップの初期値
	comboStep_ = 0;
	// コンボ間インターバルの初期値
	comboInterval_ = 30.0f;
	// コンボの進行
	comboElapse_ = 0.0f;
	// 攻撃のクールダウン
	coolDownInterval_ = 0.5f * 60.0f;
}

void LowAttack_Normal::Update()
{
	// コンボ進行タイマー更新
	if ( comboElapse_ > 0.0f ) {
		comboElapse_--;

		// タイマー終了でリセット
		if ( comboElapse_ <= 0.0f ) {
			comboStep_ = 0; 
			comboInterval_ = 0.0f;
		}
	}

	// クールダウン更新
	UpdateCoolDownTimer();
}

void LowAttack_Normal::Reset()
{

}

void LowAttack_Normal::IsAttack()
{
	// 攻撃可能でなければ何もしない
	if ( IsCoolDown() )
		return;

	// コンボ進行
	comboStep_++;

	// 弾を発射
	FireBullet();

	if ( comboStep_ >= comboMax_ )
	{
		comboStep_ = 0; // コンボをリセット

		SetAttackCoolDown(); // 基底クラスのクールダウン処理
	}

	// コンボインターバル更新
	comboElapse_ = comboInterval_;
}

void LowAttack_Normal::DrwaImGui()
{
	if ( ImGui::TreeNode("LowAttack_Normal") ) {

		ImGui::Text("comboStep : %d", comboStep_);
		ImGui::Text("comboElapse : %.1f", comboElapse_);
		ImGui::TreePop();
	}
}

void LowAttack_Normal::FireBullet()
{
	if ( auto bulMgr = bulletManager_.lock() ) {
		// Bullet生成
		auto newBul = std::make_shared<LowAttack_NormalBullet>();

		// 数値の設定
		newBul->SetPosition(owner_->GetWorldPos());

		Math::Vector::Vec3 speed{};
		if ( comboStep_ == 2 ) {
			speed = { 0.0f, 0.0f, 0.3f };
		}
		else {
			speed = { 0.0f, 0.0f, 0.6f };
		}
		newBul->SetVelocity(IMagicAttack::CalcVelocity(speed));
		newBul->SetInitPos(owner_->GetWorldPos());
		newBul->SetComboStep(comboStep_);

		// 初期化処理
		newBul->Init();

		// 名前設定
		if ( bulletCount_ == 0 ) {
			newBul->SetName(VAR_NAME(LowAttack_NormalBullet));
		}
		else {
			char name[ 32 ];
			std::snprintf(name, sizeof(name), "LowAttack_NormalBullet.%03zu", bulletCount_);
			newBul->SetName(name);
		}

		// Managerに追加
		bulMgr->PushbackNewBullet(std::move(newBul));
	}

	bulletCount_++;
}