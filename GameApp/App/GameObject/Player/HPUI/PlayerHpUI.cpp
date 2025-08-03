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

		ui->SetSize({ 384.0f, 128.0f });

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

	// --- HPゲージ用の更新処理 ---
	auto gaugeUI = hpUI_[ 1 ];

	float maxHp = 50.0f;
	float currentHp = static_cast< float >(p_playerCore_.lock()->GetHP());
	float hpRate = std::clamp(currentHp / maxHp, 0.0f, 1.0f);

	// UV座標設定（上下は反転ありなので注意）
	gaugeUI->SetLeftTop({ 0.0f, 1.0f });
	gaugeUI->SetRightTop({ hpRate, 1.0f });
	gaugeUI->SetLeftBottom({ 0.0f, 0.0f });
	gaugeUI->SetRightBottom({ hpRate, 0.0f });

	// 元のサイズ（テクスチャの本来のサイズ）
	Math::Vector::Vec2 baseSize = { 384.0f, 128.0f };

	// サイズをHP割合に合わせて縮める（左上基準なので位置は変わらない）
	gaugeUI->SetSize({ baseSize.x * hpRate, baseSize.y });

	// translateは固定のままでOK（左上基準だから）
}

void PlayerHpUI::Draw2D()
{
	for ( auto ui : hpUI_ ) {
		ui->Draw();
	}
}

