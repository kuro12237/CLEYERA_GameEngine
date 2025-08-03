#include "PlayerSkillUI_Manager.h"
#include "../Core/playerCore.h"
#include "../Scene/GameScene.h"

void PlayerSkillUI_Manager::Init()
{
    Math::Vector::Vec2 up = { 1100.0f, 530.0f };
    Math::Vector::Vec2 left = { 1045.0f, 585.0f };
    Math::Vector::Vec2 right = { 1155.0f, 585.0f };

    // UIのBG生成
    skillBg_[ 0 ] = std::make_shared<PlayerSkillUI_BG>();
    skillBg_[ 1 ] = std::make_shared<PlayerSkillUI_BG>();
    skillBg_[ 2 ] = std::make_shared<PlayerSkillUI_BG>();

    // 座標の設定
    skillBg_[ 0 ]->SetTranslate(up);
    skillBg_[ 1 ]->SetTranslate(left);
    skillBg_[ 2 ]->SetTranslate(right);
    // 名前の設定 & 初期化 & sceneにpush
    for ( size_t i = 0; i < skillBg_.size(); ++i ) {

        auto & bg = skillBg_[ i ];

        // scaleは一律
        bg->SetScale(Math::Vector::Vec2{0.08f, 0.08f});

        // 名前を一意に設定
        std::string name = "SkillUI_BG_" + std::to_string(i);
        bg->SetName(name);

        bg->Init();
        scene_->SpriteListPush(bg);
    }


	// 各UIの生成
    skillUIs_.resize(6);
	skillUIs_[int(SkillTypes::Low_Normal)] = std::make_shared<PlayerSkillUI_LowNormal>();
	skillUIs_[int(SkillTypes::Low_Back)] = std::make_shared<PlayerSkillUI_LowBack>();
	skillUIs_[int(SkillTypes::High_Normal)] = std::make_shared<PlayerSkillUI_HighNormal>();
	skillUIs_[int(SkillTypes::High_Field)] = std::make_shared<PlayerSkillUI_HighField>();
	skillUIs_[int(SkillTypes::Special_Normal) ] = std::make_shared<PlayerSkillUI_SpecialNormal>();
	skillUIs_[int(SkillTypes::Special_Power)] = std::make_shared<PlayerSkillUI_SpecialPower>();

    // それぞれのUIの座標の設定
    skillUIs_[ int(SkillTypes::Low_Normal) ]->SetTranslate(left);
    skillUIs_[ int(SkillTypes::Low_Back) ]->SetTranslate(left);
    skillUIs_[ int(SkillTypes::High_Normal) ]->SetTranslate(up);
    skillUIs_[ int(SkillTypes::High_Field) ]->SetTranslate(up);
    skillUIs_[ int(SkillTypes::Special_Normal) ]->SetTranslate(right);
    skillUIs_[ int(SkillTypes::Special_Power) ]->SetTranslate(right);

    for ( size_t index = 0; index < skillUIs_.size(); ++index ) {

        auto & sprite = skillUIs_[ index ];

        // いったん一律false
        sprite->SetActive(false);

        // scaleは一律
        sprite->SetScale(Math::Vector::Vec2{ 0.08f, 0.08f });

        // 名前リスト
        static const std::vector<std::string> skillTypeNames = {
            "Low_Normal",
            "Low_Back",
            "High_Normal",
            "High_Field",
            "Special_Normal",
            "Special_Power"
        };
        // 名前を付けて
        std::string name = "PlayerSkillUI_" + skillTypeNames[ index ];
        sprite->SetName(name);

        // 初期化
        sprite->Init();
        // sceneのlistにpush
        scene_->SpriteListPush(sprite);
    }

    // 最初の三種類だけActiveにしておく
    skillUIs_[ int(SkillTypes::Low_Normal) ]->SetActive(true);
    skillUIs_[ int(SkillTypes::High_Normal) ]->SetActive(true);
    skillUIs_[ int(SkillTypes::Special_Normal) ]->SetActive(true);
}

void PlayerSkillUI_Manager::Update()
{
}

void PlayerSkillUI_Manager::Draw2D()
{
    for ( auto bg : skillBg_ ) {
        bg->Draw();
    }

    for ( auto sprite : skillUIs_ ) {
        if(!sprite->GetActive() ) continue;
        sprite->Draw();
    }
}
