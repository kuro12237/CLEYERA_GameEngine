#include "PlayerSkillUI_Manager.h"
#include "../Core/playerCore.h"
#include "../Scene/GameScene.h"

void PlayerSkillUI_Manager::Init()
{
    // UIのBG生成
    skillBg_[ 0 ] = std::make_shared<PlayerSkillUI_BG>();
    skillBg_[ 1 ] = std::make_shared<PlayerSkillUI_BG>();
    skillBg_[ 2 ] = std::make_shared<PlayerSkillUI_BG>();

    // 座標の設定
    skillBg_[ 0 ]->SetTranslate(Math::Vector::Vec2{ 1100.0f, 530.0f });
    skillBg_[ 1 ]->SetTranslate(Math::Vector::Vec2{ 1050.0f, 580.0f });
    skillBg_[ 2 ]->SetTranslate(Math::Vector::Vec2{ 1155.0f, 580.0f});
    // 初期化 & sceneのlistにpush
    for ( auto& bg : skillBg_ ) {
        bg->Init();
        this->scene_->SpriteListPush(bg);
    }


	// 各UIの生成
    skillUIs_.resize(6);
	skillUIs_[int(SkillTypes::Low_Normal)] = std::make_shared<PlayerSkillUI_LowNormal>();
	skillUIs_[int(SkillTypes::Low_Back)] = std::make_shared<PlayerSkillUI_LowBack>();
	skillUIs_[int(SkillTypes::High_Normal)] = std::make_shared<PlayerSkillUI_HighNormal>();
	skillUIs_[int(SkillTypes::High_Field)] = std::make_shared<PlayerSkillUI_HighField>();
	skillUIs_[int(SkillTypes::Special_Normal) ] = std::make_shared<PlayerSkillUI_SpecialNormal>();
	skillUIs_[int(SkillTypes::Special_Power)] = std::make_shared<PlayerSkillUI_SpecialPower>();

    for ( size_t index = 0; index < skillUIs_.size(); ++index ) {

        auto & sprite = skillUIs_[ index ];
        // 初期化
        sprite->Init();

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
        // sceneのlistにpush
        scene_->SpriteListPush(sprite);
    }
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
        sprite->Draw();
    }
}
