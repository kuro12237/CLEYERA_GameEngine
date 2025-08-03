#include "PlayerSkillUI_HighField.h"

void PlayerSkillUI_HighField::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_HighField");
	uint32_t handle = texManager_->LoadPngTex("UI/High_Attack_Field");
	handle_ = handle;
}

void PlayerSkillUI_HighField::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
