#include "PlayerSkillUI_SpecialPower.h"

void PlayerSkillUI_SpecialPower::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_SpecialPower");
	uint32_t handle = texManager_->LoadPngTex("UI/Special_Normal");
	handle_ = handle;
}

void PlayerSkillUI_SpecialPower::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}


