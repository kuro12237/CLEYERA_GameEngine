#include "PlayerHpUI.h"
#include "../Scene/GameScene.h"

void PlayerHpUI::Init()
{
	hpUI_.resize(3);

	hpUI_[ 0 ] = std::make_shared<PlayerHpUI_Frame>();
	hpUI_[ 0 ]->SetName(VAR_NAME(PlayerHpUI_Frame));

	hpUI_[ 1 ] = std::make_shared<PlayerHpUI_Gauge>();
	hpUI_[ 1 ]->SetName(VAR_NAME(PlayerHpUI_Gauge));

	hpUI_[ 2 ] = std::make_shared<PlayerHpUI_Heart>();
	hpUI_[ 2 ]->SetName(VAR_NAME(PlayerHpUI_Heart));

	for ( auto ui : hpUI_ ) {

		// 左上基準
		ui->SetAnker({ 0.0f, 0.0f });

		ui->SetScale({ 0.2f, 0.08f });
		ui->SetTranslate({ 30.0f, 20.0f });

		ui->Init();
		scene_->SpriteListPush(ui);
	}
}

void PlayerHpUI::Update()
{
	for ( auto ui : hpUI_ ) {
		ui->Update();
	}

	float maxHp = 100.0f;

	float hpRate = std::clamp(p_playerCore_.lock()->GetHP() / maxHp, 0.0f, 1.0f);
	float baseScaleX = 0.2f;

	// HPが減るとスケールXが0.0fに近づく
	hpUI_[ 1 ]->SetScale({ baseScaleX * hpRate, 0.08f });
}

void PlayerHpUI::Draw2D()
{
	for ( auto ui : hpUI_ ) {
		ui->Draw();
	}
}

