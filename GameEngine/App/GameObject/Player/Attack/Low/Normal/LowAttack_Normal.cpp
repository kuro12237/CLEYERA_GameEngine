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
	comboInterval_ = 60.0f;
	// コンボの進行
	comboElapse_ = 0.0f;
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
}

void LowAttack_Normal::Reset()
{

}

void LowAttack_Normal::IsAttack()
{
	// 弾を発射
	FireBullet();

	// コンボ進行
	uint32_t inc = 1;
	comboStep_ = (comboStep_ + inc) % comboMax_;
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
		newBul->SetVelocity(IMagicAttack::CalcVelocity(Math::Vector::Vec3{ 0.0f, 0.0f, 0.5f }));
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